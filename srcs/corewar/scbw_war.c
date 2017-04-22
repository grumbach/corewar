/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/22 20:10:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		core_war(t_vm *vm)
{
	int	fd;
	int	i;

	i = 0;
	while (i < vm->players)
	{
		if ((fd = open(vm->core[i].prog_name, O_RDONLY)) < 0)
			errors(1, "Failed to open champion file\n");
		read(fd,  &(vm->memory[MEM_SIZE / (i + 1) * vm->players], CHAMP_MAX_SIZE);
		close(fd);
		++i;
	}
}


