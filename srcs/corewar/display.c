/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/25 00:42:17 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** display memory
*/

void		display_memory(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("\n");
	while (i < MEM_SIZE)
	{
		ft_printf("%x", vm->memory[i]);
		if (i != 0 && !(i & 1))
			ft_printf(" ");
		if (i != 0 && !(i & 127))
			ft_printf("\n");
		++i;
	}
}

/*
** display player info
*/

void			display_players(t_vm *vm)//
{
	int	i;

	i = 0;
	while (i < vm->players)
	{
		ft_printf("Introducing players :\n");
		ft_printf("Player %d : %s\n", vm->core[i].id, vm->core[i].prog_name);
		ft_printf("Magic : %06x\n", ft_endian(vm->core[i].magic));
	//	ft_printf("Weight : %s\n", ft_endian(vm->core[i].prog_size));
		ft_printf("Amy comment ? %s\n", vm->core[i].comment);
		++i;
	}	
}
