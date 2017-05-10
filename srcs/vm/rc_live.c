/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 22:43:36 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/11 01:09:31 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x01 rc_live : The instruction that allows a scv to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
** 01 00 00 00 01
** A REVOIR
**  16777216   with zork ... which is 0000 0001 ... 0000 0000 x 3
**
*/

void			rc_live(t_vm *vm, t_scv *scv)
{
    int i;

    i = 4;
   // ft_putnbr(vm->arg[0]);
   //  ft_putchar('\n');
 //   while (i--)
  //  ft_putnbr(vm->arg[0]);
    while (i < vm->nb_players)
    {
        if (scv->reg[vm->arg[0]] == vm->core[i].id)
        {
		    vm->last_id_alive = scv->reg[vm->arg[0]];
	        ++scv->live;
            ++vm->nb_total_live;
            scv->carry = 1;
            break ;
        }
        ++i;
    }
    scv->carry = 1;// a virer et corriger le live
   scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
    scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}
