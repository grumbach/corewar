/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 22:42:11 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** reverse the bytes contained inside the unsigned int n
** 0xf3 83 ea 00 ---->	0x00 ea 83 f3 EXEC MAGIC
*/

unsigned int	ft_endian(unsigned int n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) |
		((n & 0xff) << 24));
}

/*
** Original idea Clanier : checks that the args (a1 a2 a3) are the right type.
*/

int				check_arg(unsigned char type, char a1, char a2, char a3)
{
	char	a[3];

	a[0] = a1;
	a[1] = a2;
	a[2] = a3;

	if ((((type >> 6) & a[0]) != 1)
		|| (((type >> 4) & a[1]) != 1)
		|| (((type >> 2) & a[2]) != 1))
		return (FALSE);
	return (TRUE);
}

static void		cw_usage()
{
	ft_putstr_fd("\nusage: ./corewar [-"COREWAR_FLAGS"]"
		" [-dump nbr_cycles >= 0] [[-n number] champion1.cor]\n", 2);
	ft_putstr_fd("\tm : Adds music\t\t\tg : Vizualisation\t", 2);
	ft_putstr_fd("\tp : Introduce Players\n", 2);
	ft_putstr_fd("\tv : Show memory on terminal\tc : Display Cycles", 2);
	ft_putstr_fd("\t\tc : Display Threads Activity\n", 2);
}

/*
** error handler
*/

long			errors(int id, char *comment)
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
		cw_usage();
	if (id == 3)
		ft_putstr_fd(" too fat, warrior needs diet\n", 2);
	if (id == 4)
		ft_putstr_fd("Invalid Warrior Program\n", 2);
	if (id == 5)
		ft_putstr_fd("Failled to malloc a new scv\n", 2);
	exit(1);
}
