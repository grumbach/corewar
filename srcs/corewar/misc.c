/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/25 22:25:12 by angavrel         ###   ########.fr       */
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
