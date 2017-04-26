/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:27:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 17:26:55 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Creates a new process, either by fork redcode or from the .cor file
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
//	ft_putnbr(proc->coreid);//
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

    vm->nb_process = vm->nb_players;
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
}
