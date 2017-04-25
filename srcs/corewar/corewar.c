/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 00:53:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/25 22:50:16 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int ac, char **av)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	get_args(ac, av, &vm);
	get_players(&vm);
	core_war(&vm);
	return (0);
}
