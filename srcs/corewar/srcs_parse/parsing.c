/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:08:10 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/19 16:17:57 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** arg is 2 octets length
** with (arg) (arg >> 15) we get the first bite (negative or positive)
** (arg) (arg -= 0x10000) to fill with 1s except on the first bite.
*/

int		ft_negative_value(int arg)
{
	return (arg - ((arg >> 15) ? 0x10000 : 0));
}


int		ft_negative_adress(int adress)
{
	while (adress < 0)
		adress += MEM_SIZE;
	return (adress);
}

int			get_args(t_mars *vm, int type, int *n)
{
	int				arg;
	int				adress;

	arg = 0;
	if (type == T_REG)
		return (vm->memory[(vm->lst_process->pc + (*n)++) % MEM_SIZE] - 1);
	else
    {
        arg = vm->memory[(vm->lst_process->pc + (*n)++) % MEM_SIZE];
		arg <<= 8;
		arg += vm->memory[(vm->lst_process->pc + (*n)++) % MEM_SIZE];
        if (type == T_DIR)
            return (ft_negative_value(arg));
        else
		 {
            arg = ft_negative_value(arg);
		    adress = ft_negative_adress((arg + vm->lst_process->pc) % IDX_MOD);
			return (ft_negative_value(vm->memory[(adress % IDX_MOD)]));
        }
    }
}
