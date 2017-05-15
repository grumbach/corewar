/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 03:08:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/15 04:23:24 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void       play_music(void)
{
    system("afplay resources/valkyries.mp3&");
}

int			play_foam(void)
{
	system("afplay resources/scvdeath.m4a&");
	return (1);
}
