/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:40 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 16:18:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <sys/ioctl.h>

/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void		display_memory(t_vm *vm, int n)
{
	size_t	pc;
	int		i;
	struct ttysize	ts;

	if (vm->flags & F_GRAPHIC_DISPLAY)
		return ;
	pc = 0;
	if (n != 32)
	{
		ioctl(0, TIOCGWINSZ, &ts);
		n = ts.ts_cols / 3;
		i = 1;
		while (i < n)
    		i <<= 1;
		n = i >> 1;
	}
	i = 0;
	ft_printf("\n");
	if (n == 32)
		ft_printf("Reached %d Cycle, Dumping Memory :\n\n ", vm->dump);
	else
		ft_printf("\n ");
	while (pc < MEM_SIZE)
	{
		ft_printf("%02x", vm->memory[pc]);
		if ((pc % n) == (n - 1))
			ft_printf("\n ");
        else
            ft_printf(" ");
		++pc;
	}
	ft_printf("\n");
}
void		bsw(unsigned char b)//
{
	int		a[4];
	char	*s[4] = {"IND", "DIR", "REG", "..."};

	a[0] = b >> 6;
	a[1] = (b >> 4) & 3;
	a[2] = (b>> 2) & 3;
	a[3] = b & 3;

    move(68, 0);
	printw("--------------------------\n");
    printw("Base 02 ~ %d %d %d %d", a[0] / 2, a[1] / 2, a[2] / 2, a[3] / 2);//
	printw("  >>>  %s %s %s %s\n", s[0], s[1], s[2], s[3]);
	printw("Hexa 16 ~ %#11x\nBase 10 ~ %11d\n------------------------\n", b, b);
}
