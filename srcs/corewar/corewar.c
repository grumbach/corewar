/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 00:53:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/26 02:26:03 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int ac, char **av)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	get_args(ac, av, &vm, 0);
	init_cores(&vm, 0);
	if (vm.flags & F_MUSIC)	
		play_music();
	if (vm.flags & F_DISPLAY_PLAYERS)
		display_players(&vm);
	if (vm.flags & F_DISPLAY_MEM)	
		display_memory(&vm, 63);
	core_war(&vm);
	if (vm.flags & F_MUSIC)
		system("killall afplay 2&>/dev/null >/dev/null");
	return (0);
}
