/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:43:36 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/16 23:04:23 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x01 rc_live : The instruction that allows a scv to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
** 01 00 00 00 01
*/

static void		reportalive(t_vm *vm, t_scv *scv, int i)
{
	char		number[12];

	if (vm->flags & F_VISUAL)
	{
		ft_bzero(&number, sizeof(number));
		curse_puts_log(vm, scv, "OMG player ");
		ft_itoa_base_s(vm->core[i].id, 10, number);
		curse_puts_log(vm, scv, number);
		curse_puts_log(vm, scv, " (");
		curse_puts_log(vm, scv, vm->core[i].prog_name);
		curse_puts_log(vm, scv, ")");
		curse_puts_log(vm, scv, " is alive! Somebody kill him!");
	}
	else
		ft_printf("OMG player %d (%s) is alive! Somebody kill him!", \
		vm->core[i].id, vm->core[i].prog_name);
}

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
			reportalive(vm, scv, i);
		}
		++i;
	}
	scv->carry = !vm->arg[0];
}
