/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/25 01:35:12 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** display memory
*/

void		display_memory(t_vm *vm)
{
	size_t	pc;

	pc = 0;
	ft_printf("\n");
	while (pc < MEM_SIZE)
	{
		ft_printf("%02x", vm->memory[pc]);
		if ((pc % 64) == 63)
			ft_printf("\n");
        else
            ft_printf(" ");
      //  if (vm->memory[pc] == 0x0b)
        //    ft_printf("\n\n\nindex: %d\n\n\n\n\n", pc);
		++pc;
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
		ft_printf("Weight : %x\n", ft_endian(vm->core[i].prog_size));
		ft_printf("Amy comment ? %s\n", vm->core[i].comment);
		++i;
	}	
}
