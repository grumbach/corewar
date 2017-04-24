/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/25 00:42:38 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** make test && ./corewar -n 0 warriors/fluttershy.cor warriors/turtle.cor
** hexdump warriors/turtle.cor
** we check that we can 1) open the player file, 2) find the exec code at
** the beginning of file (read(fd, &magic_code, 4);), 3) store the program_name
** 4) store the comment, 5) check that code is not too long.
**
*/

void		core_war(t_vm *vm)
{
	int				fd;
	int				i;
	unsigned		size_code;
	unsigned		weight;
	
	i = 0;
	while (i < vm->players)
	{
		if ((fd = open(vm->core[i].prog_name, O_RDONLY)) < 0)
			errors(4, "Failed to open champion file\n");

		read(fd, &vm->core[i].magic, 4);
		if (ft_endian(vm->core[i].magic) != COREWAR_EXEC_MAGIC)
			errors(4, "Invalid file type, EXEC Code should be 0xea83f3");

		ft_bzero(vm->core[i].prog_name, PROG_NAME_LENGTH);
		read(fd, &vm->core[i].prog_name, PROG_NAME_LENGTH);
		ft_printf("\nPROG NAME %s\n", vm->core[i].prog_name);//

		lseek(fd, 0x88, SEEK_SET);
		read(fd, &vm->core[i].prog_size, 4);
		ft_printf("\nPROG SIZE %x\n", ft_endian(vm->core[i].prog_size));//

		ft_bzero(vm->core[i].comment, COMMENT_LENGTH);
		lseek(fd, PROG_NAME_LENGTH + 12, SEEK_SET);
		read(fd, &vm->core[i].comment, COMMENT_LENGTH);
		ft_printf("\nCOMMENT %s\n", vm->core[i].comment);// not sure comment is working properly
		
		read(fd, &(vm->memory[i * MEM_SIZE / vm->players + (i & 1)]), CHAMP_MAX_SIZE);
	//	if (size_code > CHAMP_MAX_SIZE)
	//		errors(4, "Warrior's Program too long");
		ft_printf("\n%x\n", vm->memory[i * MEM_SIZE / vm->players + (i & 1)]);//

		
		
		close(fd);
		
		
		++i;
	}
	display_players(vm);//
//	display_memory(vm);//debug
}


