/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 00:40:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/17 03:46:00 by agrumbac         ###   ########.fr       */
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
