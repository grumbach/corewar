/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 03:08:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/17 14:00:26 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		play_music(void)
{
	system("afplay resources/valkyries.mp3&");
}

void		play_foam(void)
{
	system("afplay resources/scvdeath.m4a&");
}
