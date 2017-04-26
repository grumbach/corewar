/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:58:51 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/26 17:40:00 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** adds the new process as the first element of the process list.
*/

void		add_process(t_process **process, int color, int uid)
{
    t_process	*new;

	if (!(new = new_process(fd, uid, color)))
		return (0);
	new->next = *process;
	*process = new;
	return (1);
}

/*
** converts to short
*/

short	cast_sh_int(char *tab)
{
	char integer[2];

	integer[0] = tab[1];
	integer[1] = tab[0];
	return (*((short *)integer));
}

/*
** position on the nap should not be negative
*/

int			index_memory(int index)
{
    return (index < 0 ? MEM_SIZE - (ft_abs(index) % MEM_SIZE) : index % MEM_SIZE);
}

/*
** &&& FORK INSTRUCTION &&&
**
** a new process is created with new = ft_memalloc(sizeof(t_process));
** this process will be identical to the father process (ft_memcpy)
** cycle_wait is set to 0 as the new process is already ready.
** TO_DO : add the new process to our list of process AT THE START
*/

void		rc_fork(t_vm *vm, t_proc *proc, int redcode)
{

}



t_proc	*fork(t_mars *vm, t_process *cpu, char **arg)
{
    t_proc	*new;
	short   index;
	
    new_proc(int coreid, int pc)
	ft_memcpy(new, cpu, sizeof(t_proc));
    index = cast_sh_int(arg[0]) % IDX_MOD);
	new->pc = index_memory(index + new->last_position);
    new->cycle_wait = 0;
	
	push_front_proc(&proc);

	++vm->nb_process;
}
