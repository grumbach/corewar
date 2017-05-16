/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/16 16:16:30 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** reverse the bytes contained inside the unsigned int n
** 0xf3 83 ea 00 ---->	0x00 ea 83 f3 EXEC MAGIC
*/

unsigned int	endianize(unsigned int n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) |
		((n & 0xff) << 24));
}

/*
** once vm->cycle_to_die reaches 0 it is reset
** to cycle_to_die original value - CYCLE_DELTA making next clear quicker
** we kill all scvus who didn't use live
*/

void	reset_cycle(t_vm *vm)
{
	static int	cycle_to_die = CYCLE_TO_DIE;
	t_scv		*lst;

	if (++vm->checks == MAX_CHECKS || vm->nb_total_live >= NBR_LIVE)
	{
		vm->checks = 0;
		cycle_to_die -= CYCLE_DELTA;
		if (cycle_to_die < 0)
			cycle_to_die = SUDDEN_DEATH;
	}
	vm->cycle_to_die = cycle_to_die;
	if (!(vm->flags & F_MUTE))
		play_foam();
	kill_dead_scvs(vm);
	lst = vm->scv;
	while (lst)
	{
		lst->live = 0;
		lst = lst->next;
	}
}