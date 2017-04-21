/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 02:22:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/21 23:16:04 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** get players is to parse players
** init_vm : Initialize our t_mars which is the Virtual Machine ~ init.c
** cw_play : launch the Tournament ~ corewar.c
** Once finished, display the winner's name and free our virus and VM
*/

int				main(int ac, char **av)
{
	t_mars		*vm;
	t_virus	*cpu;
	int			*option;
	int			i;

	if (ac < 2)
		display_usage(av[0]);
	i = 0;
	option = NULL;
	if (!(i = get_flags(av, ac, option, i)))
		return (ft_error("Invalid Option"));
	if (!(vm = init_vm()))
		return (ft_error("Failed to init VM"));
	vm->option = option;
	cpu = NULL;
	if (!(vm->nb_players = get_players(av, ac, cpu, i - 1)))
		return (ft_error("Invalid Player"));
	if (vm->nb_players > 4)
		return (ft_error("Too many players, 4 players max"));
	vm->dump = get_redcode(av, ac, vm->option);
	cw_play(vm, cpu);
    display_winner(vm, cpu);
	free_del_virus(cpu);
	free(vm);
	return (0);
}

/*
** -dump nbr_cycle: Dump memory after nbr_cycle executions (if game not yet
** finished) with 32 octets format by line with xx code format in hexadecimal :
** A0BCDEFE1DD3..........
** Once memory dumped, we exit game.
*/

/*
** parsing for players
** get player nb with atoi if -n is met. 
** if player has no number he given a negative number starting
** at -1 with variable j.
** !(fd = open(av[i], O_RDONLY)) >> 31) checks that number is >= 0
*/

int			get_flags(char **av, int ac, int *option, int i)
{
	vm->dump = DUMP;
	while (++i < ac && av[i][0] == '-' && ft_strcmp("-n", av[i]))
	{
		if (i < ac - 1 && !ft_strcmp("-dump", av[i]) && ++i)
			vm->dump = ft_atoi(av[i]);
		else
			if (!parse_flag(av[i], option))
				return (display_usage(av[0]));
		++i;
	}
	return (i);
}

/*
** ./corewar -{gm... optionals parameters} (-dump CYCLE_NB) (-n 1) test.core (-n 2) test2.core
** TO_DO : free what has been malloc in the list before returning 0.
*/

int			get_players(char **av, int ac, t_virus *cpu, int i)
{
	int	n;
	int	fd;
	int	nb_players;
	int	j;
	
	j = -1;
	nb_players = 0;
	while (++i < ac - 1)
	{
		n = (!ft_strcmp(av[i], "-n") && ++i) ? ft_atoi(av[i++]) : j--;
		if ((fd = open(av[i], O_RDONLY)) == -1 || !add_lst(&cpu, fd, n))
			return (0);
		else
			++nb_players;
		close(fd);
	}
	return (nb_players);
}


/*
** we look for the following letters : mg if no -dump found
** m for music
** g for graphics
** 
*/

int			parse_flag(char *s, int *flags)
{
	int		n;

	while (*(++s))
	{ 
		if ((n = ft_strchr_index("mg", *s)) < 0)
			return (0);
		*flags |= (1 << n);
	}
	return (1);
}

/*
** display USAGE and returns 0
*/

int      display_usage(char *prog_name)
{
	ft_putendl_fd("Usage : ./", 2);
	ft_putendl_fd(prog_name, 2);
    ft_putendl_fd("[-{pgwcvqm}] [-dump nbr_cycles] [[-n number] champion1.cor]", 2);
	return (0);
}
