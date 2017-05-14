/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:38:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/15 01:54:29 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Take 3 registries, add (sub) the first two, and place the result
** in the 3d, right before modifying the carry.
*/

void	rc_add(t_vm *vm, t_scv *scv)
{
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	vm->arg[1] = mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->reg[arg[2]] = arg[0] + arg[1];
	scv->carry = 1;
}

void	rc_sub(t_vm *vm, t_scv *scv)
{
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	vm->arg[1] = mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->reg[arg[2]] = arg[0] - arg[1];
	scv->carry = 1;
}
