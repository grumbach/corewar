/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:08:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/13 23:26:31 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** -dump n means that the game will finish earlier, at cycle n
*/

void	parsing(int ac, char **av, t_vm *vm, int i)
{
	int		j;

	if (!(j = 0) && ac == 1)
		errors(2, "\n");
	while (++i < ac)
		if (ft_strequ(av[i], "-dump"))
		{
			if (av[i + 1] && ft_isdigit(*av[i + 1]))
				vm->dump = ft_atoi(av[++i]);
			else
				errors(1, "go take another dump");
		}
		else if (ft_strequ(av[i], "-n"))
		{
			if (av[++i] && (ft_isdigit(*av[i]) || \
				(*av[i] == '-' && ft_isdigit(av[i][1]) && ft_atoi(av[i]) < -4)))
				get_core(av, ft_atoi(av[i]), i, vm);
			else
				errors(1, "invalid player id: should be > -1 or < -4");
			++i;
		}
		else if (*av[i] != '-')
			get_core(av, --j, i, vm);
		else if (!parse_flag(av[i], &(vm->flags)))
			errors(2, "illegal option");
}

/*
** TO_DO : add parsing if warrior program is in a subfolder.
** like ./corewar -n 0 warriors/bee_gees.s
*/

void	get_core(char **av, int n, int i, t_vm *vm)
{
	int				j;

	if (!(j = 0) && vm->nb_players == MAX_PLAYERS)
		errors(1, "too many items");
	vm->core[vm->nb_players].id = n;
//	ft_printf("%d", n);
	while (j < vm->nb_players)
		if (vm->core[j++].id == vm->core[vm->nb_players].id)
			errors(1, "one very bad id");
	if ((n < 0 && n > -5 && !av[--i]) || !av[++i])
		errors(1, "boku no champion academia");
	if (strlen(av[i]) > PROG_NAME_LENGTH)
		errors(3, av[i]);
	j = -1;
	while (++j < PROG_NAME_LENGTH)
		vm->core[vm->nb_players].prog_name[j] = av[i][j];
	vm->core[vm->nb_players].prog_name[PROG_NAME_LENGTH] = 0;
//	ft_putnbr(vm->core[vm->nb_players].id);//debug
//	ft_putendl(vm->core[vm->nb_players].prog_name);//
	++vm->nb_players;
}

int		parse_flag(char *s, int *flags)
{
	int		n;

	while (*(++s))
	{
		if ((n = flag_index(COREWAR_FLAGS, *s)) < 0)
			return (0);
		*flags |= (1 << n);
	}
	return (1);
}

int		flag_index(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

/*
** make test && ./corewar -n 0 warriors/fluttershy.cor warriors/turtle.cor
** hexdump warriors/turtle.cor
** 1) opens the player file
** 2) finds the exec code at the very first 4 bytes
** 3) then stores the program_name
** 4) stores the comment
** 5) checks that code is not too long.
**
**	!! VERIF AVEC UN PROG SIZE A 0
** !! ASK ANSELM TO CHECK THAT THE PROG SIZE IS EQUAL TO THE ACTUAL SIZE OF THE PROGRAM ~~~~A~~~~
** &&& check why lseek 0x88 wheres the 4 ?? is it padding??
** &&& IMPLEMENT MAP COLOR
** !!! MAYBE WE COULD REMOVE EXEC MAGIC FROM VARIABLE
*/

void	init_cores(t_vm *vm, int i)
{
	int				fd;

	while (i < vm->nb_players)
	{
	//	ft_printf("\nPROG NAME %s\n", vm->core[i].prog_name);//
		if ((fd = open(vm->core[i].prog_name, O_RDONLY)) < 0)
			errors(0, vm->core[i].prog_name);
		read(fd, &vm->core[i].magic, 4);
		read(fd, &vm->core[i].prog_name, PROG_NAME_LENGTH);
	//	ft_printf("\nPROG NAME %s\n", vm->core[i].prog_name);//
		lseek(fd, 0x88, SEEK_SET);
		read(fd, &vm->core[i].prog_size, 4); // !!!!!!!!!!! ON 8 BYTES!!!!!!!!!!!!
	//	ft_printf("\nPROG SIZE %x\n", ft_endian(vm->core[i].prog_size));//
	//	lseek(fd, PROG_NAME_LENGTH + 12, SEEK_SET);
		read(fd, &vm->core[i].comment, COMMENT_LENGTH + 4);
	//	ft_printf("\nCOMMENT %s\n", vm->core[i].comment);//
		if ((vm->core[i].prog_size = ft_endian(vm->core[i].prog_size))
			> CHAMP_MAX_SIZE) // this is the VALUE but maybe the file is still too big
		{
			close(fd);
			errors(1, "way.... too... much.. code.");
		}
	//	ft_printf("\nPROG SIZE %x\n", ft_endian(vm->core[i].prog_size));//
		read(fd, &(vm->memory[(vm->nb_players - i - 1) * MEM_SIZE / vm->nb_players]), vm->core[i].prog_size);
		ft_memset(&(vm->creep[(vm->nb_players - i - 1) * MEM_SIZE / vm->nb_players]), (i * 3) + 2, vm->core[i].prog_size);
	//	ft_printf("\n%x\n", vm->memory[i * MEM_SIZE / vm->nb_players + (i & 1)]);
		close(fd);
		if (ft_endian(vm->core[i].magic) != COREWAR_EXEC_MAGIC)
			errors(4, "why not 0xea83f3 ?");

//		else if (ft_endian(vm->core[i].prog_size != ) ~~~~A~~~~
		++i;
	}
//	i = -1;
//	while (++i < 4000)
//	{
//		ft_putchar('0'+ vm->creep[i]);
//	}
}
