/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 08:52:17 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/19 20:00:50 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x09 rc_zjmp : No argument’s coding byte behind this operation.
** It will take an index and jump to this address if the carry is 1.
** ex : 09 FF FB (jump back) or 09 00 08 (jump forward)
** we make sure that the final position is modulo MEM_SIZE
*/

void			rc_zjmp(t_vm *vm, t_scv *scv)
{
	if (scv->carry == 1)
	{
		scv->pc += ((signed short)vm->arg[0] - 3) % IDX_MOD;
		scv->pc &= (MEM_SIZE - 1);
	}
}
