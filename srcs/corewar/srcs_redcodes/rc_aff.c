/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:00:23 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/29 03:42:56 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
** 
*/

void        rc_aff(t_vm *vm, t_proc *proc)
{
    int		a;

    ++proc->pc;
    if (vm->memory[proc->pc++ % MEM_SIZE] != 0x40)
        return ; 
    a = vm->memory[proc->pc++ % MEM_SIZE];
    if (a > -1 && a < 16)
        ft_putchar(proc->reg[a] & 0xff);
}
