/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_scv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:27:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/17 14:09:12 by angavrel         ###   ########.fr       */
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

void	init_scv(t_vm *vm)
{
	int		i;
	t_scv	*scv;

	vm->nb_scv = vm->nb_players;
	i = vm->nb_players - 1;
	scv = new_scv();
	scv->color = (vm->nb_players << 2) - 2;
	vm->scv = scv;
	scv->reg[1] = vm->core[i].id;
	scv->pc = i * (MEM_SIZE / vm->nb_players);
	scv->pc_dst = scv->pc;
	while (i--)
	{
		scv->next = new_scv();
		scv->next->color = (i << 2) + 2;
		scv->next->reg[1] = vm->core[i].id;
		scv->next->pc = i * (MEM_SIZE / vm->nb_players);
		scv->pc_dst = scv->pc;
		scv = scv->next;
	}
}

/*
** destroy a scv if live == 0
*/

void six_pool(t_vm *vm, t_scv **scv)
{
		t_scv        *free_this;

    while (*scv)
    {
        if (!(*scv)->live)
        {
            --vm->nb_scv;
            free_this = *scv;
						if (vm->flags & F_VISUAL)
							curse_color(vm, free_this->pc, 18);
            *scv = free_this->next;
            free(free_this);
        }
        else
        {
            (*scv)->live = 0;
            scv = &(*scv)->next;
        }
    }
}

/*
** destroy scv if it looks yummy
*/

void	call_zerglings(t_scv **scv)
{
	t_scv        *free_this;

	while (*scv)
	{
		free_this = *scv;
		*scv = free_this->next;
		free(free_this);
	}
}
