/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 03:08:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/11 00:16:51 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void       play_music(void)
{
    system("afplay resources/valkyries.mp3&");
}
