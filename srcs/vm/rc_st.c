/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 00:41:52 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/22 07:50:25 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x03 rc_st : take T_REG, T_IND | T_REG and
** store the value of the registry toward a second argument.
** ie : st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
** 0b 		03 		01		[01 11]
*/

void		rc_st(void *vmp, t_scv *scv)
{
	uint	pc;
	uint	pc_tmp;
	int		i;
	t_vm	*vm;

	vm = vmp;
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	if (vm->type[1] == IND_CODE)
	{
		i = 4;
		pc = scv->pc + ((signed short)vm->arg[1]) % IDX_MOD;
		pc = clamp(pc);
		while (i--)
		{
			pc_tmp = (pc + 3 - i) % MEM_SIZE;
			vm->memory[pc_tmp] = (vm->arg[0] >> (i << 3)) & 0xff;
			vm->creep[pc_tmp] = scv->color;
			if (vm->flags & F_VISUAL)
				curse_color(vm, pc_tmp, scv->color + 1);
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

void		rc_sti(void *vmp, t_scv *scv)
{
	uint	pc;
	int		i;
	t_vm	*vm;
	uint	pc_tmp;

	vm = vmp;
	vm->arg[0] = mutate(vm, scv, vm->arg[0], vm->type[0]);
	vm->arg[1] = mutate(vm, scv, vm->arg[1], vm->type[1]);
	vm->arg[2] = mutate(vm, scv, vm->arg[2], vm->type[2]);
	i = 4;
	pc = scv->pc + ((vm->arg[1] + vm->arg[2]));
	pc = clamp(pc);
	while (i--)
	{
		pc_tmp = (pc + 3 - i) % MEM_SIZE;
		vm->memory[pc_tmp] = (vm->arg[0] >> (i << 3)) & 0xff;
		vm->creep[pc_tmp] = scv->color;
		if (vm->flags & F_VISUAL)
			curse_color(vm, pc_tmp, scv->color + 1);
	}
}
