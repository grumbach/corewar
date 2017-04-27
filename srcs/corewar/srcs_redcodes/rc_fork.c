/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:58:51 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/28 00:39:41 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x0c rc_fork : no argument’s coding byte, take T_REG. Create a
** new process that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD)).
**
** 0x0f rc_lfork : long-fork. Same as a fork without modulo in the address.
*/

void	rc_fork(t_vm *vm, t_proc *cur, int mod)
{
	t_proc	*new;

	new = new_proc(0, 0);
	ft_memcpy(new, cur, sizeof(t_proc));
	new->pc += (vm->memory[cur->pc + 2] | vm->memory[cur->pc + 1] << 8);
	cur->pc += 3;
	if (mod)
		new->pc %= (IDX_MOD);
	new->pc %= MEM_SIZE;
	new->cycle_wait = 0;
	++vm->nb_process;
	new->next = vm->proc;
	vm->proc = new;
}
