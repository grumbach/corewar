/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 18:25:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/20 16:39:27 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			ft_cmp(int data, int data_ref)
{
	if (data <= data_ref)
		return (1);
	else
		return (0);
}

void		process_remove_if(t_process **begin_list
									, int data_ref
									, int (*cmp)())
{
	t_process	*free_me;

	if (*begin_list)
	{
		if (cmp((*begin_list)->nb_live, data_ref))
		{
			free_me = *begin_list;
			*begin_list = (*begin_list)->next;
			free(free_me);
			process_remove_if(begin_list, data_ref, cmp);
		}
		else
			process_remove_if(&(*begin_list)->next, data_ref, cmp);
	}
}

/*
** start and loop until no more processus are existing.
** last_flush : decides when we refresh the UI with dump 
** we can execute instruction during
*/

void    cw_play(t_mars *vm, t_process *cpu)
{
    while (cpu)
	{
		display_vm(vm, cpu);
		if (vm->last_flush + vm->dump < vm->cycle && (*vm).modif == TRUE)
		{
			vm->last_flush = vm->cycle;
			if (vm->cycle)
				display_vm(vm, cpu);
		}
		run_cpu(&vm, &cpu);
		++vm->cycle;
		if (++vm->last_check_live >= vm->cycle_to_die)
		{
			process_remove_if(&cpu, 0, ft_cmp);
			if (!ft_check_live(&vm, &cpu)
				|| vm->cycle_to_die <= 0)
				break ;
		}
	}
}


