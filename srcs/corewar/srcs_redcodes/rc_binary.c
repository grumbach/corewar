/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 21:49:04 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 08:05:46 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

long long int	ft_get_op_arg(t_vm *vm, t_proc *proc, int type, int *n)
{
	long long int	arg;

	if (type == REG_CODE)
		return (vm->memory[(proc->pc + (*n)++) % MEM_SIZE] - 1);
	else if (type == DIR_CODE)
	{
		arg = vm->memory[(proc->pc + (*n)++) % MEM_SIZE] << 8;
		arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE];
		arg <<= 8;
		arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE];
		arg <<= 8;
		arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE];
		return (arg);
	}
	arg = vm->memory[(proc->pc + (*n)++) % MEM_SIZE] << 8;
	arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE] + proc->pc;
	return (vm->memory[(proc->pc + arg % IDX_MOD) % MEM_SIZE]);
}

int				ft_check_op_reg(t_proc *proc, char type, int *arg1, int *arg2)
{
	if (type >> 6 == 1 && (*arg1 > 15 || *arg1 < 0))
		return (0);
	else if (type >> 6 == 1)
		*arg1 = proc->reg[*arg1];
	if ((type >> 4 & 0b11) == 1 && (*arg2 > 15 || *arg2 < 0))
		return (0);
	else if ((type >> 4 & 0b11) == 1)
		*arg2 = proc->reg[*arg2];
	return (1);
}

/*
** redcode to handle AND, OR and XOR.
*/

void			rc_binary(t_vm *vm, t_proc *proc, int redcode)
{
    int             a[3];
	unsigned char	type;
	int				n;

	n = 1;
	type = vm->memory[++proc->pc % MEM_SIZE];
	if (!check_arg(type, 0b111, 0b111, 0b100))
		return ;
	a[0]= ft_get_op_arg(vm, proc, type >> 6, &n);
	a[1] = ft_get_op_arg(vm, proc, type >> 4 & 0b11, &n);
	a[2] = ft_get_op_arg(vm, proc, 1, &n);
    if (!ft_check_op_reg(proc, type, &a[0], &a[1]) || a[2] > 15 || a[2] < 0)
		return ;
	if (redcode == 0x06)
		proc->reg[a[2]] = a[0] & a[1];
	else if (redcode == 0x07)
		proc->reg[a[2]] = a[0] | a[1];
    else
        proc->reg[a[2]] = a[0] ^ a[1];
	proc->carry = proc->reg[a[2]] ? 0 : 1;
	proc->pc += n;
}