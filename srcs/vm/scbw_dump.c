/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/22 08:16:35 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void		display_winner(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->core[i].id == vm->last_id_alive)
		{
			ft_printf("\n   %sGlory and Kittens to:\n\n%s", GREEN, NORMAL);
			ft_printf("\t%sName     \
			%s%20s\n%s", GREEN, RED, vm->core[i].prog_name, NORMAL);
			ft_printf("\t%sID       \
			%s%20d\n%s", GREEN, RED, vm->core[i].id, NORMAL);
			ft_printf("\t%sWeight   \
			%s%20X\n%s", GREEN, RED, vm->core[i].prog_size, NORMAL);
			ft_printf("\t%sComment  \
			%s%20s\n\n%s", GREEN, RED, vm->core[i].comment, NORMAL);
			ft_printf("\t%sCycle    \
			%s%20d\n\n%s", GREEN, BLUE, vm->cycle, NORMAL);
			return ;
		}
		++i;
	}
	ft_printf("\n   %sWhat a bunch of loosers...\n\n%s", RED, NORMAL);
}

void		dump_memory(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...");
	while (i < vm->nb_players)
	{
		ft_printf("\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !", \
		i + 1, vm->core[i].prog_size, vm->core[i].prog_name, \
		vm->core[i].comment);
		++i;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % DUMP_SIZE))
			ft_printf("\n0x%04x : ", i);
		ft_printf("%02x ", vm->memory[i]);
		++i;
	}
	ft_printf("\n");
}
