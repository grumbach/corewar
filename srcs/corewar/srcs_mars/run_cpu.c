/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cpu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 15:34:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/20 16:04:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	get_cycle_wait(t_process *process, int opcode)
{
	if (process->cycle_wait > 0)
	{
		process->cycle_wait--;
		return ;
	}
	if (opcode == LIVE || opcode == LLD)
		process->cycle_wait = 10;
	else if (opcode == ADD || opcode == SUB)
		process->cycle_wait = 6;
	else if (opcode == ST || opcode == LD)
		process->cycle_wait = 5;
	else if (opcode == AND || opcode == OR || opcode == XOR)
		process->cycle_wait = 6;
	else if (opcode == ZJMP)
		process->cycle_wait = 20;
	else if (opcode == LDI || opcode == STI)
		process->cycle_wait = 25;
	else if (opcode == FORK)
		process->cycle_wait = 800;
	else if (opcode == LLDI)
		process->cycle_wait = 50;
	else if (opcode == LFORK)
		process->cycle_wait = 1000;
	else
		process->cycle_wait = 0;
}

static void	do_op(t_mars **vm, t_process **lst_process,
					t_process *process, int opcode)
{
	if (!process->cycle_wait && opcode == LIVE)
		ft_live(vm, process);
	else if (!process->cycle_wait && (opcode == LD || opcode == LLD))
		ft_ld(vm, process, opcode);
	else if (!process->cycle_wait && opcode == ST)
		ft_st(vm, process);
	else if (!process->cycle_wait && (opcode == ADD || opcode == SUB))
		ft_add_sub(vm, process, opcode);
	else if (!process->cycle_wait &&
					(opcode == AND || opcode == OR || opcode == XOR))
		ft_binary(vm, process, opcode);
	else if (!process->cycle_wait && opcode == ZJMP)
		ft_zjmp(vm, process);
	else if (!process->cycle_wait && opcode == STI)
		ft_sti(vm, process, 0);
	else if (!process->cycle_wait && (opcode == FORK || opcode == LFORK))
		ft_fork(lst_process, vm, process, opcode);
	else if (!process->cycle_wait && (opcode == LDI || opcode == LLDI))
		ft_ldi(vm, process, opcode);
	else if (!process->cycle_wait)
		process->pc++;
}

void		run_cpu(t_mars **vm, t_process **lst_process)
{
	t_process			*process;
	unsigned char		op_code;

	process = *lst_process;
	(*vm)->nb_process = 0;
	while (process)
	{
		op_code = (*vm)->memory[process->pc % MEM_SIZE];
		get_cycle_wait(process, op_code);
		do_op(vm, lst_process, process, op_code);
		process = process->next;
		(*vm)->nb_process++;
		op_code = 0;
	}
}