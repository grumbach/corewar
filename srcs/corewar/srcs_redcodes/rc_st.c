/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 00:41:52 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/28 00:55:07 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int	    get_st_arg(t_vm *vm, t_proc *proc, int type, int *n)
{
	int	arg;

	if (type == T_REG)
		return (vm->memory[(proc->pc + (*n)++) % MEM_SIZE] - 1);
	arg = vm->memory[(proc->pc + (*n)++) % MEM_SIZE] << 8;
	arg += vm->memory[(proc->pc + (*n)++) % MEM_SIZE] + proc->pc;
	return (vm->memory[(proc->pc + arg % IDX_MOD) % MEM_SIZE]);
}


/*
** 0x03 rc_st : take T_REG, T_IND | T_REG and
** store the value of the registry toward a second argument.
** ie : st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
*/

void			rc_st(t_vm *vm, t_proc *proc)
{
    int             a[2];
	unsigned char	type;
	int				n;

	type = vm->memory[++proc->pc % MEM_SIZE];
  //  ft_putnbr(type);//
	if (!check_arg(type, 0b100, 0b111, 0b110))
		return ;
    n = 1;
	a[0] = get_st_arg(vm, proc, REG_CODE, &n); // should be a register
	a[1] = get_st_arg(vm, proc, type >> 4 & 0b11, &n); //
  //  ft_putchar('\n');ft_putnbr(a[0]);ft_putchar('\n');//
    //ft_putnbr(a[1]);ft_putchar('\n');//
  //  ft_putnbr(a[2]);ft_putchar('\n');//
	if (a[0] >= REG_NUMBER || a[0] < 0
    || ((type >> 2 & 0b11) == 1 && (a[1] >= REG_NUMBER || a[1] < 0)))
		return ;
    proc->reg[a[0]] = a[0];  
    proc->pc += n;
}