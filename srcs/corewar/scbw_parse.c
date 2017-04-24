/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:08:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/25 01:43:57 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			flag_index(char *s, int c)
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

static int			parse_flag(char *s, int *flags)
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

/*
** TO_DO : add parsing if warrior program is in a subfolder. like ./corewar -n 0 warriors/bee_gees.s
*/

static void			get_core(char **av, int n, int i, t_vm *vm)
{
	int				j;

	if (!(j = 0) && vm->players == MAX_PLAYERS)
		errors(1, "Too many players\n");
	vm->core[vm->players].id = n;
//	ft_printf("%d", n);
	while (j < vm->players)
		if (vm->core[j++].id  == vm->core[vm->players].id)
			errors(1, "Choose different ids for your champions\n");
	if ((n < 0 && n > -5 && !av[--i]) || !av[++i])
		errors(1, "No champion\n");
	if (strlen(av[i]) > PROG_NAME_LENGTH)
		errors(3, av[i]);
	j = -1;
	while (++j < PROG_NAME_LENGTH)
		vm->core[vm->players].prog_name[j] = av[i][j];
	vm->core[vm->players].prog_name[PROG_NAME_LENGTH] = 0;
//	ft_putnbr(vm->core[vm->players].id);//debug
//	ft_putendl(vm->core[vm->players].prog_name);//
	++vm->players;
}

void				get_args(int ac, char **av, t_vm *vm)
{
	int		i;
	int		j;

	if (!(i = 0) && !(j = 0) && ac == 1)
		errors(1, 0);
	while (++i < ac)
		if (ft_strequ(av[i], "-dump"))
		{
			if (av[i + 1] && ft_isdigit(av[i + 1][0]))
				vm->dump = ft_atoi(av[i + 1]);
			else
				errors(1, "go take another dump");
		}
		else if (ft_strequ(av[i], "-n"))
		{
			if (av[++i] && (ft_isdigit(av[i][0]) || 
			(av[i][0] == '-' && ft_isdigit(av[i][1]) && ft_atoi(av[i]) < -4)))
				get_core(av, ft_atoi(av[i]), i, vm);
			else
				errors(1, "invalid player id: should be numerical > -1 or < -4");
			++i;
		}
		else if (av[i][0] == '-' && !parse_flag(av[i], &(vm->flags)))
			errors(1, "illegal option");
		else
			get_core(av, --j, i++, vm);
}

/*
** make test && ./corewar -n 0 warriors/fluttershy.cor warriors/turtle.cor
** hexdump warriors/turtle.cor
** we check that we can 1) open the player file, 2) find the exec code at
** the beginning of file (read(fd, &magic_code, 4);), 3) store the program_name
** 4) store the comment, 5) check that code is not too long.
**
*/

void		get_players(t_vm *vm)
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
		ft_bzero(vm->core[i].prog_name, PROG_NAME_LENGTH + 1);
		read(fd, &vm->core[i].prog_name, PROG_NAME_LENGTH + 1);
	//	ft_printf("\nPROG NAME %s\n", vm->core[i].prog_name);//
		lseek(fd, 0x88, SEEK_SET);
		read(fd, &vm->core[i].prog_size, 4);
	//	ft_printf("\nPROG SIZE %x\n", ft_endian(vm->core[i].prog_size));//
		ft_bzero(vm->core[i].comment, COMMENT_LENGTH + 4);
		lseek(fd, PROG_NAME_LENGTH + 12, SEEK_SET);
		read(fd, &vm->core[i].comment, COMMENT_LENGTH + 4);
	//	ft_printf("\nCOMMENT %s\n", vm->core[i].comment);//	
		read(fd, &(vm->memory[i * MEM_SIZE / vm->players]), CHAMP_MAX_SIZE);
	//	ft_printf("\n%x\n", vm->memory[i * MEM_SIZE / vm->players + (i & 1)]);//	
		close(fd);
		if (ft_endian(vm->core[i].magic) != COREWAR_EXEC_MAGIC)
			errors(4, "Invalid file type, EXEC Code should be 0xea83f3");
		else if (ft_endian(vm->core[i].prog_size) > CHAMP_MAX_SIZE)
			errors(4, "Warrior's Program too long");
		++i;
	}
}
