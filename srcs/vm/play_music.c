/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 03:08:18 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 16:13:11 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void       play_music(void)
{
    system("afplay ./music/aivi_answer.mp3&");
}
