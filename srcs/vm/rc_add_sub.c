/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:38:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/16 16:24:05 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Take 3 registries, add (sub) the first two, and place the result
** in the 3d, right before modifying the carry.
** plesae refer to rc_binary.c file for rc_calc func.
*/

void	rc_add(t_vm *vm, t_scv *scv)
{
	rc_calc(vm, scv);
	scv->reg[vm->arg[2]] = change_carry(&scv->carry, vm->arg[0] + vm->arg[1]);
}

void	rc_sub(t_vm *vm, t_scv *scv)
{
	rc_calc(vm, scv);
	scv->reg[vm->arg[2]] = change_carry(&scv->carry, vm->arg[0] - vm->arg[1]);
}
