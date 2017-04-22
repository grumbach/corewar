/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:08:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/23 01:10:31 by angavrel         ###   ########.fr       */
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

int             ft_strrevequ(const char *s1, const char *s2)
{
        int     i;
		int		j;

		i = ft_strlen(s1) - 1;
		j = ft_strlen(s2) - 1;
        if (!s1 && !s2)
                return (1);
        else if (!s1 || !s2)
                return (0);
        while (i && s1[i--] == s2[j])
            if (--j == 0 && i)
                return (1);
        return (0);
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
	while (j < vm->players)
		if (vm->core[j++].id  == vm->core[vm->players].id)
			errors(1, "Choose different ids for your champions\n");
	if (n < 0 && n > -5 && !av[--i])
		errors(1, "No champion\n");
	else if (!av[++i])
		errors(1, "No champion\n");
	if (strlen(av[i]) > PROG_NAME_LENGTH)
		errors(3, av[i]);
	j = -1;
	while (++j < PROG_NAME_LENGTH)
		vm->core[vm->players].prog_name[j] = av[i][j];
	vm->core[vm->players].prog_name[PROG_NAME_LENGTH] = 0;
	ft_putnbr(vm->core[vm->players].id);//debug
	ft_putendl(vm->core[vm->players].prog_name);//
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
				errors(1, "invalid player id");
			++i;
		}
		else if (av[i][0] == '-' && !parse_flag(av[i], &(vm->flags)))
			errors(1, "illegal option");
		else
			get_core(av, --j, i++, vm);
}
