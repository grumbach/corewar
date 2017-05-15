/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/13 22:00:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** reverse the bytes contained inside the unsigned int n
** 0xf3 83 ea 00 ---->	0x00 ea 83 f3 EXEC MAGIC
*/

unsigned int	endianize(unsigned int n)
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
