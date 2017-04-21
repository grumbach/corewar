/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 12:57:01 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/21 23:18:10 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** make sure no virus remain to avoid memory leaks
*/

free_del_virus(t_virus *lst_virus)
{
    t_virus   *tmp;

	while (virus)
	{
        tmp = vm->virus;
        free(tmp);
        tmp = NULL;
        virus = lst_virus->next;
    }
}
