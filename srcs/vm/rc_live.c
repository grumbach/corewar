/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:43:36 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/16 18:22:43 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x01 rc_live : The instruction that allows a scv to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
** 01 00 00 00 01
*/

void			rc_live(t_vm *vm, t_scv *scv)
{
	int			i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->core[i].id == vm->arg[0])
		{
			vm->last_id_alive = vm->arg[0];
			++scv->live;
			++vm->nb_total_live;
		}
		++i;
	}
	scv->carry = !vm->arg[0];
}
