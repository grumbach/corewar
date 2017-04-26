/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:43:36 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 08:22:42 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x01 rc_live : The instruction that allows a process to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
*/

void			rc_live(t_vm *vm, t_proc *proc)
{
    int		id;

    if (proc->coreid == (id = (int)vm->memory[++proc->pc % MEM_SIZE]))
		vm->last_id_alive = id;
//    ft_putchar('\n');ft_putnbr(id);ft_putchar('\n');
  //  ft_putnbr(proc->pc);
    proc->pc += 3;
  //  ft_putchar('\n');ft_putnbr(vm->memory[proc->pc]);
	++proc->live;
}