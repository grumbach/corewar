/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:49:04 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/16 16:24:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x06 rc_and : Apply an & (bit-to-bit AND) over the first two arguments and
** store the result in a registry, which is the 3d argument. Modifies the carry
*/

void			rc_and(t_vm *vm, t_scv *scv)
{
	rc_calc(vm, scv);
	scv->reg[vm->arg[2]] = change_carry(&scv->carry, vm->arg[0] & vm->arg[1]);
}

/*
** 0x07 rc_or : This operation is an bit-to-bit OR.
*/

void			rc_or(t_vm *vm, t_scv *scv)
{
	rc_calc(vm, scv);
	scv->reg[vm->arg[2]] = change_carry(&scv->carry, vm->arg[0] | vm->arg[1]);
}

/*
** 0x08 rc_xor : Acts like and with an exclusive OR.
*/

void			rc_xor(t_vm *vm, t_scv *scv)
{
	rc_calc(vm, scv);
	scv->reg[vm->arg[2]] = change_carry(&scv->carry, vm->arg[0] ^ vm->arg[1]);
}
