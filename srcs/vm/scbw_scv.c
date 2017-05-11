/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_scv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:27:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/11 04:04:58 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Creates a new scv, either with (rc_fork.c) or due to the .cor file
*/

t_scv	*new_scv(int coreid, int pc)
{
	t_scv	*scv;

	if (!(scv = (t_scv *)ft_memalloc(sizeof(t_scv))))
		errors(5, 0);
	ft_bzero(scv->reg, sizeof(scv->reg));
	scv->next = NULL;
	scv->live = 0; // check if it shouldnt be 1 ?
	scv->pc = pc;
	scv->carry = 0;
	scv->cooldown = 0;
	scv->reg[1] = coreid;
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

	vm->scv = NULL;
    vm->nb_scv = vm->nb_players;
//	ft_putnbr(vm->nb_players);//
    i = vm->nb_players - 1;
    scv = new_scv(vm->core[i].id, (vm->nb_players - i - 1) * MEM_SIZE / vm->nb_players);
	vm->last_id_alive = vm->core[i].id;
    while (i--)
    {
        scv->next = new_scv(vm->core[i].id, (vm->nb_players - i - 1) * MEM_SIZE / vm->nb_players);
        if (i + 2 == vm->nb_players)
            vm->scv = scv;
        scv = scv->next;
    }
    if (vm->nb_players == 1)
        vm->scv = scv;
//		ft_putnbr(vm->nb_scv);//
}

/*
** once vm->cycle_to_die reaches 0 it is reset
** to cycle_to_die original value - CYCLE_DELTA making next clear quicker
** we kill all scvus who didn't use live
*/

void	reset_cycle(t_vm *vm)
{
	static int	cycle_to_die = CYCLE_TO_DIE;

	if (++vm->checks == 10 || vm->nb_total_live >= 21) // 9 // CHECKS == 10| 9 // verif si superieur ou egal ou juste superieur
		vm->checks = 0;
	vm->cycle_to_die = cycle_to_die - (!vm->checks ? CYCLE_DELTA : 0);
}

/*
** destroy a scv if live == 0
*/

void	kill_scv(t_vm *vm, t_scv **scv)
{
	t_scv		*lst;
	t_scv		*tmp;

	lst = *scv;
	while (lst)
	{
		if (lst->next)
		{
			if (!lst->next->live--)
			{
				tmp = lst->next;
				lst->next = lst->next->next ? lst->next->next : NULL; // not sure if ternary is mandatory... have to check
				ft_memdel((void **)&tmp);
        		--vm->nb_scv;
			}
			else
				--vm->nb_total_live; // !!!!!!!a verifier !!
		}
		lst = lst->next;
	}
	--vm->nb_total_live;
	if (*scv && !((*scv)->live--) && vm->nb_scv--)
    {
        tmp = (*scv);
		(*scv) = (*scv)->next; // if first item is dead then the next one become the first.
		ft_memdel((void **)&tmp);
    }
}

/* ANSELM TO_DO_LIST
void	kill_all_scv(t_vm *vm, t_scv **scv)
{
	t_scv		*lst;
	t_scv		*tmp;

	lst = *scv;
	while (lst)
	{
		if (lst->next)
		{
			if (!lst->next->live--)
			{
				tmp = lst->next;
				lst->next = lst->next->next ? lst->next->next : NULL; // not sure if ternary is mandatory... have to check
				ft_memdel((void **)&tmp);
        		--vm->nb_scv;
			}
			else
				--vm->nb_total_live; // !!!!!!!a verifier !!
		}
		lst = lst->next;
	}
	--vm->nb_total_live;
	if (*scv && !((*scv)->live--) && vm->nb_scv--)
    {
        tmp = (*scv);
		(*scv) = (*scv)->next; // if first item is dead then the next one become the first.
		ft_memdel((void **)&tmp);
    }
}
*/