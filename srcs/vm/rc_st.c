/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 00:41:52 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 23:44:15 by angavrel         ###   ########.fr       */
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
	uint	pc;
	int		i;
	uint	n;

	pc = 0;
	n = scv->reg[vm->arg[0]];
	i = 4;
	while (i--)
	{
		if (vm->flags & F_VISUAL)
			
		vm->memory[(pc + (3 - i) % IDX_MOD) & (MEM_SIZE - 1)]
			= (n >> (i << 3)) & 0xff;
	}
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}

/*
** 0x0b rc_sti :
** a[0] = T_REG, a[1] = T_REG | T_DIR | T_IND, a[2] = T_DIR | T_REG
** ex: 		0b 	(68)  01 		[01 (10) 11] 		[01 (10)]
** add the two indexes, and use this result as an address where the value of
** the first parameter will be copied.
** Example :
** Type = 104 means 01,10,10,00 in binary : a[0] as reg, a[1] and a[2] as dir
**
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3 sont
** des registres, on utilisera leur contenu comme un index.
*/

void				rc_sti(t_vm *vm, t_scv *scv)
{
	uint		pc;
	int			i;
	uint		n;

	if (vm->type[1] == IND_CODE)
		vm->arg[1] %= IDX_MOD;
	if (vm->type[2] == IND_CODE)
		vm->arg[2] %= IDX_MOD;
	pc = (vm->arg[1] + vm->arg[2]) & (MEM_SIZE - 1);
	n = scv->reg[vm->arg[0]];
	i = REG_SIZE;
	while (i--)
	{
		if (vm->flags & F_DISPLAY_SCV)
		{
			attron(COLOR_PAIR(3));
			mvprintw(3 + scv->pc / vm->curse.n, 1 + (scv->pc % vm->curse.n) * 3,
				"%02x", vm->memory[(pc + 3 - i) & (MEM_SIZE - 1)]);
			attroff(COLOR_PAIR(3));
		}
		vm->memory[(pc + 3 - i) & (MEM_SIZE - 1)] = (n >> (i << 3)) & 0xff;
	}
	scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}
