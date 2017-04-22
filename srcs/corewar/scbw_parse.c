/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:08:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/22 16:25:05 by angavrel         ###   ########.fr       */
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

static void			get_core(char **av, int n, t_vm *vm)
{
	vm->core->id = n;

	ft_putnbr(vm->core->id);
	(void)av;
}

void				get_args(int ac, char **av, t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	if (!(j = 0) && ac == 1)
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
			if (av[++i] && ft_isdigit(av[i][0]))
				get_core(av, ft_atoi(av[i]), vm);
			else
				errors(1, "invalid player id");
		}
		else if (av[i][0] == '-' && !parse_flag(av[i], &(vm->flags)))
			errors(1, "illegal option");
		else
			get_core(av, --j, vm);
}
