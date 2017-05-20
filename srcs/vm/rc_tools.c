/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 02:00:21 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/20 10:11:21 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** dereferencing IND and REG
*/

uint	mutate(t_vm *vm, t_scv *scv, uint raw, unsigned char type)
{
	int			i;
	int			n;

	if (type == REG_CODE)
		return (scv->reg[raw]);
	else if (type == IND_CODE)
	{
		if (vm->redcode < 13)
			raw %= IDX_MOD;
		i = scv->pc + raw;
		n = DIR_SIZE;
		while (n--)
			raw = vm->memory[i++ % MEM_SIZE] | (raw << 8);
	}
	else if (vm->rc[vm->redcode].dir_size == 2)
		raw = (signed short)raw;
	return (raw);
}

uint	clamp(int raw)
{
	return (((raw % MEM_SIZE) + MEM_SIZE) & (MEM_SIZE - 1));
}
