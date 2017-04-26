/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 17:04:07 by angavrel         ###   ########.fr       */
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
	if (n == 31)
		ft_printf("Reached %d Cycle, Dumping Memory :\n\n\t", vm->dump);
	else
		ft_printf("\n\t");
	while (pc < MEM_SIZE)
	{
		ft_printf("%02x", vm->memory[pc]);
		if ((pc & n) == n)
			ft_printf("\n\t");
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
	ft_printf("\nIntroducing our Gladiators, Ave Caesar, Morituri te salutant :\n\n");
	while (i < vm->nb_players)
	{	
		ft_printf("\tPlayer %d : %s\n", vm->core[i].id, vm->core[i].prog_name);
		ft_printf("\tMagic : %06x\n", ft_endian(vm->core[i].magic));
		ft_printf("\tWeight : %x\n", ft_endian(vm->core[i].prog_size));
		ft_printf("\tAmy comment ? %s\n", vm->core[i].comment);
		ft_putchar('\n');
		++i;
	}	
}
