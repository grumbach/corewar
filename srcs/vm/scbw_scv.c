/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_scv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:27:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/17 02:23:41 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Creates a new scv, either with (rc_fork.c) or due to the .cor file
*/

t_scv	*new_scv(void)
{
	t_scv	*scv;

	if (!(scv = (t_scv *)ft_memalloc(sizeof(t_scv))))
		errors(0, 0);
	return (scv);
}

/*
** Initialize the scv belonging to each warrior
** the last warriors given as arg start first
*/

void				init_scv(t_vm *vm)
{
    int             i;
    t_scv          *scv;

    vm->nb_scv = vm->nb_players;
    i = vm->nb_players - 1;
	scv = new_scv();
	scv->color = vm->nb_players * 3 - 1;
	vm->scv = scv;
	scv->reg[1] = vm->core[i].id;
	scv->pc = (vm->nb_players - i - 1) * (MEM_SIZE / vm->nb_players);
    while (i--)
    {
        scv->next = new_scv();
		scv->next->color = i * 3 + 2;
		scv->next->reg[1] = vm->core[i].id;
		scv->next->pc = (vm->nb_players - i - 1) * (MEM_SIZE / vm->nb_players);
        scv = scv->next;
    }
}

/*
** destroy a scv if live == 0
*/

void	kill_dead_scvs(t_vm *vm)
{
	t_scv		*lst;
	t_scv		*tmp;

	lst = vm->scv;
	while (lst)
	{
		if (lst->next && !lst->next->live)
		{
			if (vm->flags & F_VISUAL)
				curse_color(vm, lst->next->pc, 14);
			curse_puts_log(vm, lst->next, "hello!");
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp);
			--vm->nb_scv;
		}
		--vm->nb_total_live;
		lst = lst->next;
	}
	if (!vm->scv->live)
	{
		tmp = vm->scv;
		vm->scv = vm->scv->next;
		free(tmp);
	}
	werase(vm->curse.win2);
	wrefresh(vm->curse.win2);
}

void		call_zerglings(t_scv *scv)
{
	if (scv && scv->next)
		call_zerglings(scv->next);
	free(scv);
}
