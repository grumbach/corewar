/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:58:51 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/23 00:51:06 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x0c rc_fork : no argument’s coding byte, take T_REG. Create a
** new scv that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD)).
** 0x0f rc_lfork : long-fork. Same as a fork without modulo in the address.
*/

void		rc_fork(void *vmp, t_scv *cur)
{
	t_scv	*new;
	t_vm	*vm;

	vm = vmp;
	new = new_scv();
	ft_memcpy(new, cur, sizeof(t_scv));
	new->cooldown = 0;
	new->redcode = 0;
	new->next = vm->scv;
	vm->scv = new;
	++vm->nb_scv;
	new->pc = clamp(new->pc + (signed short)vm->arg[0] % IDX_MOD);
	new->redcode = vm->memory[new->pc % MEM_SIZE];
	if (0 < new->redcode && new->redcode < 17)
		new->cooldown = vm->rc[new->redcode].cooldown - 1;
	else
		new->redcode = 0;
}

void		rc_lfork(void *vmp, t_scv *cur)
{
	t_scv	*new;
	t_vm	*vm;

	vm = vmp;
	new = new_scv();
	ft_memcpy(new, cur, sizeof(t_scv));
	new->cooldown = 0;
	new->redcode = 0;
	new->next = vm->scv;
	vm->scv = new;
	++vm->nb_scv;
	new->pc = clamp(new->pc + (signed short)vm->arg[0]);
	new->redcode = vm->memory[new->pc % MEM_SIZE];
	if (0 < new->redcode && new->redcode < 17)
		new->cooldown = vm->rc[new->redcode].cooldown - 1;
	else
		new->redcode = 0;
}
