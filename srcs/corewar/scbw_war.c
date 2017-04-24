/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/24 21:43:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** display memory
*/

void		display_memory(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("\n");
	while (i < MEM_SIZE)
	{
		ft_printf("%x", vm->memory[i]);
		if (i != 0 && !(i & 1))
			ft_printf(" ");
		if (i != 0 && !(i & 127))
			ft_printf("\n");
		++i;
	}
}


/*
** make test && ./corewar -n 0 warriors/fluttershy.cor warriors/turtle.cor
** hexdump warriors/turtle.cor
** we check that we can 1) open the player file, 2) find the exec code at
** the beginning of file (read(fd, &magic_code, 4);), 3) that code_size is
** not too big (lseek(fd, 0x80 + 8, SEEK_SET);)
** Finally code is directly stored in the VM.
** lseek
**
*/

void		core_war(t_vm *vm)
{
	int	fd;
	int	i;
	unsigned	size_code;
	unsigned int	magic_code;
	
	i = 0;
	while (i < vm->players)
	{
		if ((fd = open(vm->core[i].prog_name, O_RDONLY)) < 0)
			errors(1, "Failed to open champion file\n");
		read(fd, &magic_code, 4);
		lseek(fd, 4, SEEK_SET);
		read(fd, &size_code, 4);
		lseek(fd, 0x80 + 8, SEEK_SET);
		read(fd, &size_code, 4);
		lseek(fd, PROG_NAME_LENGTH - 4, SEEK_SET);
		read(fd, &vm->core[i].comment, COMMENT_LENGTH);
		ft_printf("\n%s\n", vm->core[i].comment);
		ft_printf("\n%x\n", CHAMP_MAX_SIZE);
		lseek(fd, sizeof(header_t), SEEK_SET);
		read(fd, &(vm->memory[i * MEM_SIZE / vm->players + (i & 1)]), CHAMP_MAX_SIZE);
		close(fd);
		if (magic_code != COREWAR_EXEC_MAGIC_REVERSE)
			errors(1, "Invalid EXEC Code, should be 0xea83f3");
		else if (size_code < CHAMP_MAX_SIZE)
			errors(1, "Chammpion is too big");
		++i;
	}
	display_memory(vm);//debug
}


