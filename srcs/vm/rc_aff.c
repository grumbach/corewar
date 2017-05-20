/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:00:23 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/20 02:32:27 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
*/

void		rc_aff(void *vm, t_scv *scv)
{
	if (vm->flags & F_RC_AFF)
	{
		vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]) & 0xff;
		if (vm->flags & F_VISUAL)
			curse_puts_log(vm, scv, (char[2]){vm->arg[0], '\0'});
		else
			ft_putchar(vm->arg[0]);
	}
}
