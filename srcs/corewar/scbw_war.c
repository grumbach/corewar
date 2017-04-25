/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/25 03:59:19 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x01 op_live : The instruction that allows a process to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
**
** 0x02 op_ld : Take a random argument and a registry. Load the value of the 1st
** argument in the registry and will change the carry.
**
** 0x0d op_lld : Means long-load. It the same as ld, but without % IDX_MOD.
** Modify the carry.
**
** 0x03 op_st : take a registry and (a registry || an indirect) and
** store the value of the registry toward a second argument.
** ie : st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
**
** 0x04 op_add : Take 3 registries, add the first two, and place the result
** in the 3d, right before modifying the carry.
**
** 0x05 op_sub : same as add but with a substraction.
**
** 0x06 op_and : Apply an & (bit-to-bit AND) over the first two arguments and
** store the result in a registry, which is the 3d argument. Modifies the carry
**
** 0x07 op_or : This operation is an bit-to-bit OR.
**
** 0x08 op_xor : Acts like and with an exclusive OR.
**
** 0x09 op_zjmp : No argument’s coding byte behind this operation.
** It will take an index and jump to this address if the carry is 1.
**
** 0x0a op_ldi : ldi will use 2 indexes and 1 registry, adding the first
** two, treating that like an address, reading a value of a registry’s size
** and putting it on the third.
**
** 0x0e op_lldi : Same as ldi, but does not apply any modulo to the addresses.
** It will however, modify the carry
**
** 0x0b op_sti : Take a registry, and two indexes (potentially registries),
** add the two indexes, and use this result as an address where the value of 
** the first parameter will be copied.
**
** 0x0c op_fork : no argument’s coding byte, take an index. Create a
** new process that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD)).
**
** 0x0f op_lfork : long-fork. Same as a fork without modulo in the address.
**
** 0x10 op_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
*/

/*
void	*fetch(t_vm *vm, t_proc *proc, int opcode)
{
	if (opcode == 0x01)
		op_live(vm, proc);
	else if (opcode == 0x02 || opcode == 0x0d)
		op_ld(vm, proc, opcode);
	else if (opcode == 0x03)
		op_st(vm, proc);
	else if (opcode == 0x04 || opcode == 0x05)
		op_add_sub(vm, proc, (opcode & 1) ? -1 : 1);
	else if (opcode == 0x06 || opcode == 0x07 || opcode == 0x08)
		op_binary(vm, proc, opcode);
	else if (opcode == 0x09)
		op_zjmp(vm, proc);
	else if (opcode == 0x0a || opcode == 0x0e)
		op_ldi(vm, proc, opcode);
	else if (opcode == 0x0b)
		op_sti(vm, proc);
	else if (opcode == 0x0c || opcode == 0x0f)
		op_fork(vm, proc, (16 - opcode) >> 2);
	else if (opcode == 0x10)
		op_aff(vm, proc);
	else
		++proc->pc;
}*/

void		core_war(t_vm *vm)
{
	if (vm->flags & 1)	
		play_music();
	if (vm->flags & 4)
		display_players(vm);
	if (vm->flags & 8)	
		display_memory(vm);
	vm->pc = 0;
	while (42)
	{
		opcode = vm->memory[vm->pc % MEM_SIZE];
	//	fetch(vm, &vm->proc, opcode) 
		break;

//		vm->proc = vm->proc->next;
	}
	if (vm->flags & 1)
		system("killall afplay 2&>/dev/null >/dev/null");
	// display winner
}
