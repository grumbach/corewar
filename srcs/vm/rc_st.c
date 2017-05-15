/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 00:41:52 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/15 15:59:29 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x03 rc_st : take T_REG, T_IND | T_REG and
** store the value of the registry toward a second argument.
** ie : st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
** 0b 		03 		01		[01 11]
*/

void	rc_st(t_vm *vm, t_scv *scv)
{
	int		pc;
	int		i;

	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	if (vm->type[1] == IND_CODE)
	{
		i = 4;
		pc = scv->pc + vm->arg[1] & (IDX_MOD - 1);
		while (i--)
		{
			vm->memory[(pc + 3 - i) & (MEM_SIZE - 1)] = \
				(vm->arg[0] >> (i << 3)) & 0xff;
			vm->creep[(pc + 3 - i) & (MEM_SIZE - 1)] = scv->color;
			if (vm->flags & F_VISUAL)
				curse_color(vm, (pc + 3 - i) & (MEM_SIZE - 1), \
				scv->color + 1);
		}
	}
	else if (vm->type[1] == REG_CODE)
		scv->reg[vm->arg[1]] = vm->arg[0];
}

/*
** 0x0b rc_sti :
** sti: Opcode 11. Take a registry, and two indexes (potentially registries)
** add the two indexes, and use this result as an address where the value of
** the first parameter will be copied.
*/

void				rc_sti(t_vm *vm, t_scv *scv)
{
	int		pc;
	int		i;

	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	vm->arg[1] = mutate(vm, scv, vm->arg[1], vm->type[1]);
	vm->arg[2] = mutate(vm, scv, vm->arg[2], vm->type[2]);
	i = 4;
	pc = scv->pc + ((vm->arg[1] + vm->arg[2]) & (IDX_MOD - 1));
	while (i--)
	{
		vm->memory[(pc + 3 - i) & (MEM_SIZE - 1)] = \
			(vm->arg[0] >> (i << 3)) & 0xff;
		vm->creep[(pc + 3 - i) & (MEM_SIZE - 1)] = scv->color;
		if (vm->flags & F_VISUAL)
			curse_color(vm, (pc + 3 - i) & (MEM_SIZE - 1), scv->color + 1);
	}
}
