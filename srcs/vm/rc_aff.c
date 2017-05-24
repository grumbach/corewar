/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:00:23 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/24 02:14:43 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
*/

void		rc_aff(void *vmp, t_scv *scv)
{
	t_vm	*vm;

	vm = vmp;
	if (vm->flags & F_RC_LOG)
	{
		vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]) & 0xff;
		if (vm->flags & F_VISUAL)
			curse_puts_log(vm, scv, (char[2]){vm->arg[0], '\0'});
		else
			ft_putchar(vm->arg[0]);
	}
}

/*
** function to display messages and aff inside the log window
*/

void		curse_puts_log(t_vm *vm, t_scv *scv, char *s)
{
	static int	y[MAX_PLAYERS] = {0, 0, 0, 0};
	static int	x[MAX_PLAYERS] = {0, 0, 0, 0};
	const int	i = (scv->color - 2) / 4;

	if (y[i] > 13)
	{
		y[i] = 0;
		while (y[i] < 14)
			curse_puts_log(vm, scv, " ");
		y[i] = 0;
		x[i] = 0;
	}
	if (x[i] + (int)ft_strlen(s) > (vm->curse.n * 3 - 3) / \
		vm->nb_players && ++y[i])
		x[i] = 0;
	wmove(vm->curse.wlog, 1 + y[i], 1 + \
	x[i] + (i) * (vm->curse.n * 3 - 3) / vm->nb_players);
	wattron(vm->curse.wlog, COLOR_PAIR(scv->color));
	if (y[i] < 14)
		wprintw(vm->curse.wlog, s);
	wattroff(vm->curse.wlog, COLOR_PAIR(scv->color));
	x[i] += ft_strlen(s);
	if (ft_strchr(s, '!') && ++y[i])
		x[i] = 0;
	wrefresh(vm->curse.wlog);
}
