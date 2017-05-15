/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_scv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:27:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/15 05:00:17 by agrumbac         ###   ########.fr       */
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
	vm->scv = scv;
	scv->reg[1] = vm->core[i].id;
	scv->pc = (vm->nb_players - i - 1) * (MEM_SIZE / vm->nb_players);
    while (i--)
    {
        scv->next = new_scv();
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
	while (lst && lst->next)
	{
		if (!lst->next->live)
		{
			if (vm->flags & F_VISUAL)
				curse_color(vm, lst->next, lst->next->pc, 14);
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
}

static void	zergling(void *scv, size_t i)
{
	i = 42;
	free(scv);
}

void		kill_all_scvs(t_vm *vm)
{
	void	*alst;

	alst = &(vm->scv);
	ft_printf("hi");//
	ft_lstdel((t_list**)alst, &zergling);
	ft_printf("a\n");//
}
