/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 02:37:13 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** reverse the bytes contained inside the unsigned int n
*/

unsigned int	ft_endian(unsigned int n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) |
		((n & 0xff) << 16));
}

/*
** Original idea Clanier : checks that the args (a1 a2 a3) are the right type.
*/

int				check_arg(unsigned char type, char a1, char a2, char a3)
{
	char	a[3];
	int		i;

	a[0] = a1;
	a[1] = a2;
	a[2] = a3;
	i = -1;
	while (++i < 3)
		if ((!(a[i] & T_IND) && type >> 6 == REG_CODE)
				|| (!(a[i] & T_DIR) && type >> 6 == DIR_CODE)
				|| (!(a[i] & T_REG) && type >> 6 == IND_CODE))
			return (FALSE);
	return (TRUE);
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
		ft_putstr_fd("\nusage: ./corewar [-"COREWAR_FLAGS"]"
			" [-dump nbr_cycles >= 0] [[-n number] champion1.cor]\n", 2);
	if (id == 3)
		ft_putstr_fd(" too fat, warrior needs diet\n", 2);
	if (id == 4)
		ft_putstr_fd("Invalid Warrior Program\n", 2);
	if (id == 5)
		ft_putstr_fd("Failled to malloc a new proc\n", 2);
	ft_putstr_fd("m : Adds music\t\t\tg : Vizualisation\t", 2);
	ft_putstr_fd("p : Introduce Players\n", 2);
	ft_putstr_fd("v : Show memory on terminal\tc : Display Cycles\n", 2);
	exit(1);
}
