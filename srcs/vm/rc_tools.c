/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 02:00:21 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/24 09:46:20 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** reverse the bytes contained inside the unsigned int n
** 0xf3 83 ea 00 ---->	0x00 ea 83 f3 EXEC MAGIC
*/

uint	endianize(unsigned int n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) |
		((n & 0xff) << 24));
}

/*
** dereferencing IND and REG
*/

int		mutate(t_vm *vm, t_scv *scv, int raw, unsigned char type)
{
	int			i;
	int			n;

	if (type == REG_CODE)
		return (scv->reg[raw]);
	else if (type == IND_CODE)
	{
		if (scv->redcode < 13)
			raw %= IDX_MOD;
		i = scv->pc + raw;
		n = DIR_SIZE;
		while (n--)
			raw = vm->memory[i++ % MEM_SIZE] | (raw << 8);
	}
	else if (vm->rc[scv->redcode].dir_size == 2)
		raw = (signed short)raw;
	return (raw);
}

int		clamp(int raw)
{
	return ((raw % MEM_SIZE + MEM_SIZE) & (MEM_SIZE - 1));
}
