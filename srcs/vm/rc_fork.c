/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:58:51 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 16:15:45 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x0c rc_fork : no argument’s coding byte, take T_REG. Create a
** new scv that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD)).
**
** 0x0f rc_lfork : long-fork. Same as a fork without modulo in the address.
*/

void	rc_fork(t_vm *vm, t_scv *cur)
{
	t_scv	*new;

//	mvprintw(70, 5, "POSITION %d", cur->pc);//
	new = new_scv(0, 0);
	ft_memcpy(new, cur, sizeof(t_scv));
	new->cooldown = 0;
	new->next = vm->scv;
	vm->scv = new;
	++vm->nb_scv;
	new->pc = vm->memory[(cur->pc + 1) & (MEM_SIZE - 1)] << 8;
	new->pc |= vm->memory[(cur->pc + 2) & (MEM_SIZE - 1)];
	new->pc &= (IDX_MOD - 1);
	new->pc += cur->pc;
	new->pc &= (MEM_SIZE - 1);
	cur->pc += 3;
	cur->pc &= (MEM_SIZE - 1);
}

void	rc_lfork(t_vm *vm, t_scv *cur)
{
	t_scv	*new;

	new = new_scv(0, 0);
	ft_memcpy(new, cur, sizeof(t_scv));
	new->cooldown = 0;
	new->next = vm->scv;
	vm->scv = new;
	++vm->nb_scv;
	new->pc = vm->memory[(cur->pc + 1) & (MEM_SIZE - 1)] << 8;
	new->pc |= vm->memory[(cur->pc + 2) & (MEM_SIZE - 1)];
	new->pc += cur->pc;
	new->pc &= (MEM_SIZE - 1);
	cur->pc += 3;
	cur->pc &= (MEM_SIZE - 1);
}
