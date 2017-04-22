/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 00:53:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/22 02:12:21 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

long		errors(int id, char *comment)//get fct lemin
{
	ft_putstr_fd("corewar: ", 2);
	if (comment)
	{
		ft_putstr_fd(comment, 2);
		ft_putstr_fd(" ", 2);
	}
	if (id == 0)
		ft_putendl_fd(strerror(errno), 2);
	if (id == 1)
		ft_putstr_fd("\nusage: ./corewar [-"COREWAR_FLAGS"]"
			" [-dump nbr_cycles] [[-n number] champion1.cor]\n", 2);
	exit(1);
}

int			main(int ac, char **av)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	get_args(ac, av, &vm);
	core_war(&vm);
	return (0);
}
