/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:38:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/29 02:13:36 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Take 3 registries, add (sub) the first two, and place the result
** in the 3d, right before modifying the carry.
** plus_minus is equal to 1 if add and -1 if sub.
** first we do ++proc->pc; to check the type
*/

void	rc_add_sub(t_vm *vm, t_proc *proc, int plus_minus)
{
	unsigned int	reg[3]; // maybe signed ?
	int				i;

	ft_printf("add function\n");
	if (check_arg(vm->memory[++proc->pc % MEM_SIZE], REG_CODE, REG_CODE, REG_CODE))
    {
		ft_printf("okay lets do it\n");
        i = -1;
	    while (++i < 3)
		    if ((reg[i] = vm->memory[(proc->pc + i) % MEM_SIZE] - 1) >> 4) // maybe use ft_endian ? depends on the storage
			    return ;
		proc->reg[2] = proc->reg[0] + (plus_minus * proc->reg[1]);
	    proc->carry = proc->reg[2] ? 0 : 1;
	    proc->pc += 4;
    }
}
