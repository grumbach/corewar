/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 09:21:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 16:15:29 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x02 rc_ld : Take a random argument and a registry (T_DIR | T_IND, T_REG).
** Load the value of the argument in the registry and will change the carry.
*/

void			rc_ld(t_vm *vm, t_scv *scv)
{
	if (vm->type[0] == IND_CODE)
		vm->arg[0] &= (IDX_MOD - 1);
	scv->reg[vm->arg[1]] = vm->arg[0];     // IDX MOOD fonly for INDI
	scv->carry = 1;
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}

/*
** 0x0d rc_lld : Means long-load. It the same as ld, but without % IDX_MOD.
** Also modifies the carry.
*/

void			rc_lld(t_vm *vm, t_scv *scv)
{
	scv->reg[vm->arg[1]] = vm->arg[0] & (MEM_SIZE - 1);
	scv->carry = 1;
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}

/*
** {&rc_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1},
** add 2 first arg and then treat it like an address, Read REG_SIZE and put in
** the last arg which is a reg
*/

void			rc_ldi(t_vm *vm, t_scv *scv)
{
	uint	pc;
	int		i;

	if (vm->type[0] == IND_CODE)
		vm->arg[0] %= IDX_MOD;
	pc = (vm->arg[0] + vm->arg[1]);
	i = REG_SIZE;
	scv->reg[vm->arg[2]] = 0;
	while (i--)
		scv->reg[vm->arg[2]] |= vm->memory[(pc + 3 - i) & (MEM_SIZE - 1)]
			<< (i << 1);
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}

/*
** same as ldi but with no modulo applied (IDX MOD when IND) to addresses. change carry
*/

void			rc_lldi(t_vm *vm, t_scv *scv)
{
	const uint	pc = (vm->arg[0] + vm->arg[1]);
	int			i;

	i = REG_SIZE;
	scv->reg[vm->arg[2]] = 0;
	while (i--)
	{
		scv->reg[vm->arg[2]] |= vm->memory[(pc + 3 - i) & (MEM_SIZE - 1)]
			<< (i << 1);
	}
	scv->carry = 1;
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}
