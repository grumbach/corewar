/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/11 00:25:30 by agrumbac         ###   ########.fr       */
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
	int	i;

	i = 0;
	ft_printf("\n   %sGlory to our surviving gladiator :\n\n%s", GREEN, NORMAL);
	while (i < vm->nb_players)
	{
		if (vm->core[i].id == vm->last_id_alive)
		{
			ft_printf("\t%sName     \
			%s%20s\n%s", GREEN, RED, vm->core[i].prog_name, NORMAL);
			ft_printf("\t%sID       \
			%s%20d\n%s", GREEN, RED, vm->core[i].id, NORMAL);
			ft_printf("\t%sComment  \
			%s%20s\n%s", GREEN, RED, vm->core[i].comment, NORMAL);
			ft_printf("\t%sWeight   \
			%s%20X\n\n%s", GREEN, RED, vm->core[i].prog_size, NORMAL);
			ft_printf("\t%sCycle    \
			%s%20X\n\n%s", GREEN, BLUE, vm->cycle, NORMAL);
			break;
		}
		++i;
	}
}

void		dump_memory(t_vm *vm)
{
	size_t	pc;

	ft_printf("Reached cycle %d, now dumping memory :\n\n ", vm->dump);
	pc = 0;
	while (pc < MEM_SIZE)
	{
		ft_printf("%02x", vm->memory[pc]);
		if ((pc & 31) == 31)
			ft_printf("\n ");
        else
            ft_printf(" ");
		++pc;
	}
	ft_printf("\n");
}
