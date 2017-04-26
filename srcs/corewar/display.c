/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 02:01:07 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void		display_memory(t_vm *vm, int n)
{
	size_t	pc;

	pc = 0;
	ft_printf("\n");
	while (pc < MEM_SIZE)
	{
		ft_printf("%02x", vm->memory[pc]);
		if ((pc & n) == n)
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
