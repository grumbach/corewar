/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:49:04 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/17 05:46:38 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x04 rc_add : Take 3 registries, add (sub) the first two, and place the
** result in the 3d, right before modifying the carry.
*/

void			rc_add(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = mutate(vm, scv, vm->arg[0], vm->type[0]) \
		+ mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry ^= scv->carry;
}

/*
** 0x05 rc_sub : see above
*/

void			rc_sub(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = mutate(vm, scv, vm->arg[0], vm->type[0]) \
		- mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry ^= scv->carry;
}

/*
** 0x06 rc_and : Apply an & (bit-to-bit AND) over the first two arguments and
** store the result in a registry, which is the 3d argument. Modifies the carry
*/

void			rc_and(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = mutate(vm, scv, vm->arg[0], vm->type[0]) \
		& mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry ^= scv->carry;
}

/*
** 0x07 rc_or : This operation is an bit-to-bit OR.
*/

void			rc_or(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = mutate(vm, scv, vm->arg[0], vm->type[0]) \
		| mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry ^= scv->carry;
}

/*
** 0x08 rc_xor : Acts like and with an exclusive OR.
*/

void			rc_xor(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[2]] = mutate(vm, scv, vm->arg[0], vm->type[0]) \
		^ mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry ^= scv->carry;
}
