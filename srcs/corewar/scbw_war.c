/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/25 06:29:48 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** AFF is for trolling purpose only :X
*/

void	rc_cost(int *cycle_wait, int redcode)
{
	if (redcode == AFF)
		*cycle_wait = 2;
	else if (redcode == LD || redcode == ST)
		*cycle_wait = 5;
	else if (redcode == AND || redcode == OR || redcode == XOR)
		*cycle_wait = 6;
	else if (redcode == LIVE || redcode == ADD || redcode == SUB || redcode == LLD)
		*cycle_wait = 10;
	else if (redcode == ZJMP)
		*cycle_wait = 20;
	else if (redcode == LDI || redcode == STI)
		*cycle_wait = 25;
	else if (redcode == LLDI)
		*cycle_wait = 50;
	else if (redcode == FORK)
		*cycle_wait = 800;
	else if (redcode == LFORK)
		*cycle_wait = 1000;
	
}

/*
** 0x01 rc_live : The instruction that allows a process to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
**
** 0x02 rc_ld : Take a random argument and a registry. Load the value of the 1st
** argument in the registry and will change the carry.
**
** 0x0d rc_lld : Means long-load. It the same as ld, but without % IDX_MOD.
** Modify the carry.
**
** 0x03 rc_st : take a registry and (a registry || an indirect) and
** store the value of the registry toward a second argument.
** ie : st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
**
** 0x04 rc_add : Take 3 registries, add the first two, and place the result
** in the 3d, right before modifying the carry.
**
** 0x05 rc_sub : same as add but with a substraction.
**
** 0x06 rc_and : Apply an & (bit-to-bit AND) over the first two arguments and
** store the result in a registry, which is the 3d argument. Modifies the carry
**
** 0x07 rc_or : This operation is an bit-to-bit OR.
**
** 0x08 rc_xor : Acts like and with an exclusive OR.
**
** 0x09 rc_zjmp : No argument’s coding byte behind this operation.
** It will take an index and jump to this address if the carry is 1.
**
** 0x0a rc_ldi : ldi will use 2 indexes and 1 registry, adding the first
** two, treating that like an address, reading a value of a registry’s size
** and putting it on the third.
**
** 0x0e rc_lldi : Same as ldi, but does not apply any modulo to the addresses.
** It will however, modify the carry
**
** 0x0b rc_sti : Take a registry, and two indexes (potentially registries),
** add the two indexes, and use this result as an address where the value of 
** the first parameter will be copied.
**
** 0x0c rc_fork : no argument’s coding byte, take an index. Create a
** new process that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD)).
**
** 0x0f rc_lfork : long-fork. Same as a fork without modulo in the address.
**
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
*/

void	*fetch(t_vm *vm, t_proc *proc, int redcode)
{
	if (redcode == 0x01)
		rc_live(vm, proc);
	else if (redcode == 0x02 || redcode == 0x0d)
		rc_ld(vm, proc, redcode);
	else if (redcode == 0x03)
		rc_st(vm, proc);
	else if (redcode == 0x04 || redcode == 0x05)
		rc_add_sub(vm, proc, (redcode & 1) ? -1 : 1);
	else if (redcode == 0x06 || redcode == 0x07 || redcode == 0x08)
		rc_binary(vm, proc, redcode);
	else if (redcode == 0x09)
		rc_zjmp(vm, proc);
	else if (redcode == 0x0a || redcode == 0x0e)
		rc_ldi(vm, proc, redcode);
	else if (redcode == 0x0b)
		rc_sti(vm, proc);
	else if (redcode == 0x0c || redcode == 0x0f)
		rc_fork(vm, proc, (16 - redcode) >> 2);
	else if (redcode == 0x10)
		rc_aff(vm, proc);
	else
		++proc->pc;
}

/*
** go through our processus list and :
** 1) check for redcode instructions redcode = vm->memory[lst->pc % MEM_SIZE];
** 2) check how long it will have to wait rc_cost(&lst->cycle_wait, redcode);
** 3) execute the redcode : fetch(vm, lst, redcode);
*/

void		get_proc_redcode(t_vm *vm, t_proc **proc)
{
	t_proc		*lst;
	int			redcode;

	lst = *proc;
	vm->nb_process = 0;
	while (lst)
	{
		redcode = vm->memory[lst->pc % MEM_SIZE];
		if (!((lst->cycle_wait--)))
			rc_cost(&lst->cycle_wait, redcode);
		fetch(vm, lst, redcode);
		lst = lst->next;
	}
}

/*
** once vm->cycle_to_die reaches 0 it is reset
** to cycle_to_die original value - CYCLE_DELTA making next clear quicker
*/

int		kill_proc(t_vm *vm, t_proc **proc)
{
	t_proc		*lst;
	static int	cycle_to_die = CYCLE_TO_DIE;

	cycle_to_die -= CYCLE_DELTA;
	vm->cycle_to_die = cycle_to_die;
	lst = *proc;
	while (lst)
	{
		// kill proc if list->live not alive
		lst = lst->next;
	}
	return (1);
}

/*
** Our main program
*/

void		core_war(t_vm *vm)
{
	t_proc	*proc;
	
	proc = NULL;
	if (vm->flags & 1)	
		play_music();
	if (vm->flags & 4)
		display_players(vm);
	if (vm->flags & 8)	
		display_memory(vm);
//	proc->pc = 0;
	vm->cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	while (vm->cycle < 10)
	{
		if (vm->flags & 16 && ft_printf("%d Cycles left\n", vm->cycle_to_die))
			ft_printf("\nCycle %d\n", vm->cycle);
		get_proc_redcode(vm, &proc);
		if (!vm->cycle_to_die--)  // does cycle 0 exist?
			kill_proc(vm, &proc);
		++vm->cycle;
	}
	if (vm->flags & 1)
		system("killall afplay 2&>/dev/null >/dev/null");
	// display winner
}
