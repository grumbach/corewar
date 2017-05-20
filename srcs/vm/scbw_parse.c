/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:08:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/20 03:22:44 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** reverse the bytes contained inside the unsigned int n
** 0xf3 83 ea 00 ---->	0x00 ea 83 f3 EXEC MAGIC
*/

uint		endianize(unsigned int n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) |
		((n & 0xff) << 24));
}

static int	flag_index(char *s, int c)
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

static int	parse_flag(char *s, int *flags, t_vm *vm)
{
	int		n;

	while (*(++s))
	{
		if ((n = flag_index(COREWAR_FLAGS, *s)) < 0)
			return (0);
		*flags |= (1 << n);
		if ((1 << n) == F_DUMP_FREQUENCY)
		{
			if (*(s + 1) && ft_isdigit(*(s + 1)) && ((n = ft_atoi(++s)) > 0))
				vm->dump = n;
			else
				return (0);
			while (ft_isdigit(*s))
				++s;
			--s;
		}
	}
	return (1);
}

static void	get_core(char **av, int n, int i, t_vm *vm)
{
	int		j;

	j = 0;
	if (vm->nb_players == MAX_PLAYERS)
		errors(1, "too many items");
	vm->core[vm->nb_players].id = n;
	while (j < vm->nb_players)
		if (vm->core[j++].id == vm->core[vm->nb_players].id)
			errors(1, "one very bad id");
	if (!av[i])
		errors(1, "no champion academia");
	j = -1;
	while (av[i][++j])
		vm->core[vm->nb_players].prog_name[j] = av[i][j];
	++vm->nb_players;
}

void		parsing(int ac, char **av, t_vm *vm, int i)
{
	int		j;

	if (!(j = 0) && ac == 1)
		errors(2, "");
	while (++i < ac)
		if (ft_strequ(av[i], "-dump") && (vm->flags |= F_DUMP))
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
				get_core(av, ft_atoi(av[i]), i + 1, vm);
			else
				errors(1, "invalid player id: should be > -1 or < -4");
			++i;
		}
		else if (*av[i] != '-')
			get_core(av, --j, i, vm);
		else if (!parse_flag(av[i], &(vm->flags), vm))
			errors(2, "illegal option");
}
