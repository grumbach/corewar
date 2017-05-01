/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:27:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/29 02:55:01 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Creates a new process, either with (rc_fork.c) or due to the .cor file
*/

t_proc	*new_proc(int coreid, int pc)
{
	t_proc	*proc;

	if (!(proc = (t_proc *)ft_memalloc(sizeof(t_proc))))
		errors(5, 0);
	proc->next = NULL;
	proc->live = 0; // check if it shouldnt be 1 ?
	proc->pc = pc;
	proc->carry = 0;
	proc->cycle_wait = 0;
	proc->coreid = coreid;
	proc->reg[0] = proc->coreid;
	ft_bzero(proc->reg, sizeof(proc->reg));
	return (proc);
}

/*
** Initialize the process belonging to each warrior
** the last warriors given as arg start first
*/

void				init_proc(t_vm *vm)
{
    int             i;
    t_proc          *proc;

	vm->proc = NULL;
    vm->nb_process = vm->nb_players;
//	ft_putnbr(vm->nb_players);//
    i = vm->nb_players - 1;
    proc = new_proc(vm->core[i].id, (vm->nb_players - i - 1) * MEM_SIZE / vm->nb_players);
    while (i--)
    {   
        proc->next = new_proc(vm->core[i].id, (vm->nb_players - i - 1) * MEM_SIZE / vm->nb_players);
        if (i + 2 == vm->nb_players)
            vm->proc = proc;
        proc = proc->next;
    }
    if (vm->nb_players == 1)
        vm->proc = proc;
//		ft_putnbr(vm->nb_process);//
}

/*
** once vm->cycle_to_die reaches 0 it is reset
** to cycle_to_die original value - CYCLE_DELTA making next clear quicker
** we kill all processus who didn't use live
*/

void	reset_cycle(t_vm *vm)
{
	static int	cycle_to_die = CYCLE_TO_DIE;

	if (++vm->checks == 10 || vm->nb_total_live >= 21) // 9 // CHECKS == 10| 9 // verif si superieur ou egal ou juste superieur
	{
		vm->checks = 0;
		vm->nb_total_live = 0;
	}
	vm->cycle_to_die = cycle_to_die - (!vm->checks ? CYCLE_DELTA : 0); //	reinitialization
}

void	kill_proc(t_vm *vm, t_proc **proc)
{
	t_proc		*lst;
	t_proc		*tmp;

	lst = *proc;
	while (lst)
	{
		if (lst->next && !lst->next->live--)
		{
			tmp = lst->next;
			tmp = NULL;
			free(tmp);
            --vm->nb_process;
			lst->next = lst->next->next ? lst->next->next : NULL; // not sure if ternary is mandatory... have to check
		}
		lst = lst->next;
	}
	if (*proc && !((*proc)->live--) && vm->nb_process--)
    {
        tmp = (*proc);
        tmp = NULL;
        free(tmp);
		(*proc) = (*proc)->next; // if first item is dead then the next one become the first.
    }
}
