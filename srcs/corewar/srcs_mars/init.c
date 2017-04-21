/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:40:03 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/21 01:07:05 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** initialize our VM which is a t_mars
*/

t_mars		*init_vm(t_mars *vm)
{
	if (!(vm = (t_mars *)ft_memalloc(sizeof(t_mars))))
		return (0);//exit(EXIT_FAILURE);
    ft_bzero(vm, sizeof(vm));
	init_memory(&vm);
//	init_processus(vm);
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->modif = TRUE;
	return (vm);
}

/*
** get redcode instructions of the champion
** dump is set to DUMP (20) and will return this value if unchanged.
*/

int			get_redcode(char **av, int ac, int *option)
{
	int		i;
	int		dump;

	i = 0;
	dump = DUMP;
	while (++i < ac && *av[i] == '-')
	{
		if (!ft_strcmp(av[i], "-dump") && (i < ac - 1))
			dump = ft_atoi(av[++i]);
		else if (!ft_strcmp(av[i], "-p"))
			*option = 1;
	}
	return (dump);
}

/*
** initialize memory
*/

void	init_memory(t_mars **vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		(*vm)->memory[i] = 0;
		(*vm)->memory_color[i] = 0;
		++i;
	}
}


/*
** get_range checks the distance between players
** distance is set to MEM_SIZE which is the max distance possible
**    ...
**
*/

static int	get_range(t_process *lst_process)
{
	int		distance;
	int		i;

	distance = MEM_SIZE;
	i = 0;
	while (lst_process)
	{
		distance -= lst_process->size_code;
		lst_process = lst_process->next;
		++i;
	}
	return ((distance / i));
}

/*
** ask JGB about this function
*/

void	    init_processus(t_mars *vm)
{
	int			distance;
	t_xy		i;
	t_process	*tmp;

    distance = get_range(vm->lst_process);
    tmp = vm->lst_process;
	i.y = 0;
	i.x = 0;
	while (tmp)
	{
		tmp->pc = i.y;
		while (i.x < tmp->size_code)
		{
			vm->memory[i.y] = tmp->code[i.x];
			vm->memory_color[i.y] = tmp->color;
			++i.x;
			++i.y;
		}
		tmp = tmp->next;
		i.y += distance;
		i.x = 0;
        i.y -=i.y - (i.y % SIZE_LINE);
	}
}
