/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 09:21:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/22 07:51:46 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x02 rc_ld : Take a random argument and a registry (T_DIR | T_IND, T_REG).
** Loads the value of the argument in the registry and changes the carry.
*/

void			rc_ld(void *vmp, t_scv *scv)
{
	t_vm	*vm;

	vm = vmp;
	scv->carry = !( \
	scv->reg[vm->arg[1]] = mutate(vm, scv, vm->arg[0], vm->type[0]));
}

/*
** 0x0d rc_lld : Means long-load. Similar to ld, but without % IDX_MOD.
** Also modifies the carry.
*/

void			rc_lld(void *vmp, t_scv *scv)
{
	t_vm	*vm;

	vm = vmp;
	scv->carry = !( \
	scv->reg[vm->arg[1]] = mutate(vm, scv, vm->arg[0], vm->type[0]));
}

/*
** {&rc_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1},
** add 2 first arg and then treat it like an address, Read REG_SIZE and put in
** the last arg which is a reg
*/

void			rc_ldi(void *vmp, t_scv *scv)
{
	t_vm	*vm;

	vm = vmp;
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	vm->arg[1] = mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry = !( \
	scv->reg[vm->arg[2]] = \
		mutate(vm, scv, (vm->arg[0] + vm->arg[1]) % MEM_SIZE, IND_CODE));
}

/*
** same as ldi but with no modulo applied (IDX MOD when IND) to addresses.
** change carry mutate function takes care of the IDX MOD.
*/

void			rc_lldi(void *vmp, t_scv *scv)
{
	t_vm	*vm;

	vm = vmp;
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	vm->arg[1] = mutate(vm, scv, vm->arg[1], vm->type[1]);
	scv->carry = !( \
	scv->reg[vm->arg[2]] = \
		mutate(vm, scv, (vm->arg[0] + vm->arg[1]) % MEM_SIZE, IND_CODE));
}
