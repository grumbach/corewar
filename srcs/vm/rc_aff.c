/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:00:23 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 16:30:58 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
** adding  a = vm->memory[scv->pc++ % MEM_SIZE] - 1; to transform reg to index 
*/

void        rc_aff(t_vm *vm, t_scv *scv)
{
    ft_putchar(scv->reg[vm->arg[0]] & 0xff);
    scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}
