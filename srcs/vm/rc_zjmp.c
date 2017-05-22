/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 08:52:17 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/22 03:22:05 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x09 rc_zjmp : No argument’s coding byte behind this operation.
** It will take an index and jump to this address if the carry is 1.
** ex : 09 FF FB (jump back) or 09 00 08 (jump forward)
** we make sure that the final position is modulo MEM_SIZE
*/

void			rc_zjmp(void *vmp, t_scv *scv)
{
	t_vm	*vm;

	vm = vmp;
	if (scv->carry == 1)
	{
		scv->pc_dst += ((signed short)vm->arg[0] % IDX_MOD) - 3;
		scv->pc_dst = clamp(scv->pc_dst);
	}
}
