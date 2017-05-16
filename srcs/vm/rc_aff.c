/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:00:23 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/16 17:19:16 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	curse_putchar_log(t_vm *vm, t_scv *scv)
{
	char	a[2];
	int			i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->core[i].id == scv->reg[1])
		{
			a[0] = vm->arg[0];
			a[1] = 0;
			wattron(vm->curse.win, COLOR_PAIR((2 + vm->core[i].color)));
			mvwprintw(vm->curse.win, 68, 2, a);
			wattroff(vm->curse.win, COLOR_PAIR((2 + vm->core[i].color)));
		//	ft_putnbr(vm->core[3].color); //!!!!! fix color
		}
		++i;
	}
}

/*
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
*/

void        rc_aff(t_vm *vm, t_scv *scv)
{
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]) & 0xff;
	if (vm->flags & F_VISUAL)
		curse_putchar_log(vm, scv);
	else
		ft_putchar(vm->arg[0]);
}
