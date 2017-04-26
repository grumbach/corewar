/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 06:47:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 08:24:26 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int	    get_sti_arg(t_vm *vm, t_proc *proc, int type, int *n)
{
	int	arg;

	if (type == T_REG)
		return (vm->memory[(proc->pc + (*n)++) % MEM_SIZE] - 1);
	else if (type == T_DIR)
	{
		arg = vm->memory[(proc->pc + (*n)++) % MEM_SIZE] << 8;
		arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE];
		if (arg >> 15)
			arg -= 0x10000;
		return (arg);
	}
	arg = vm->memory[(proc->pc + (*n)++) % MEM_SIZE] << 8;
	arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE] + proc->pc;
	return (vm->memory[(proc->pc + arg % IDX_MOD) % MEM_SIZE]);
}

/*
** 0x0b rc_sti : 
** a[0] = T_REG, a[1] = T_REG | T_DIR | T_IND, a[2] = T_DIR | T_REG
** add the two indexes, and use this result as an address where the value of 
** the first parameter will be copied.
** Example :
** Type = 104 means 01,10,10,00 in binary : a[0] as reg, a[1] and a[2] as dir
*/

void			rc_sti(t_vm *vm, t_proc *proc)
{
    int             a[3];
	unsigned char	type;
	int				n;

	type = vm->memory[++proc->pc % MEM_SIZE];
  //  ft_putnbr(type);//
	if (!check_arg(type, 0b100, 0b111, 0b110))
		return ;
    n = 1;
	a[0] = get_sti_arg(vm, proc, REG_CODE, &n);
	a[1] = get_sti_arg(vm, proc, type >> 4 & 0b11, &n);
	a[2] = get_sti_arg(vm, proc, type >> 2 & 0b11, &n);
  //  ft_putchar('\n');ft_putnbr(a[0]);ft_putchar('\n');//
    //ft_putnbr(a[1]);ft_putchar('\n');//
  //  ft_putnbr(a[2]);ft_putchar('\n');//
	if (a[0] >= REG_NUMBER || a[0] < 0
    || ((type >> 4 & 0b11) == 1 && (a[1] >= REG_NUMBER || a[1] < 0))
    || ((type >> 2 & 0b11) == 1 && (a[2] >= REG_NUMBER || a[2] < 0)))
		return ;
    else
	    proc->pc += n;
}
