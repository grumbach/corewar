/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:38:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 16:17:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Take 3 registries, add (sub) the first two, and place the result
** in the 3d, right before modifying the carry.
*/

void	rc_add(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = scv->reg[vm->arg[0]] + scv->reg[vm->arg[1]];
	scv->carry = scv->reg[vm->arg[2]] ? 0 : 1;
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
	(void)vm;
}

void	rc_sub(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = scv->reg[vm->arg[0]] - scv->reg[vm->arg[1]];
	scv->carry = scv->reg[vm->arg[2]] ? 0 : 1;
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
	(void)vm;
}
