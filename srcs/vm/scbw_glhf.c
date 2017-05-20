/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_glhf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/20 11:39:39 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** once vm->cycle_to_die reaches 0 it is reset
** to cycle_to_die original value - CYCLE_DELTA making next clear quicker
** we kill all scvs who didn't use live
*/

static void	reset_cycle(t_vm *vm)
{
	static int	cycle_to_die = CYCLE_TO_DIE;

	if (++vm->checks == MAX_CHECKS || vm->nb_total_live >= NBR_LIVE)
	{
		vm->checks = 0;
		cycle_to_die -= CYCLE_DELTA;
		if (cycle_to_die < 0)
			cycle_to_die = SUDDEN_DEATH;
	}
	vm->cycle_to_die = cycle_to_die;
	if (!(vm->flags & F_MUTE))
		play_foam();
	vm->scv = six_pool(vm, vm->scv);
	vm->nb_total_live = 0;
	curse_clear_scvs(&vm->curse);
}

static int	user_input(t_vm *vm)
{
	int		key;

	key = wgetch(vm->curse.wmem);
	if (key == KEY_PLUS && vm->curse.speed < 10)
		++vm->curse.speed;
	else if (key == KEY_MINUS && vm->curse.speed > 0)
		--vm->curse.speed;
	else if (key == KEY_SPACE)
	{
		if (vm->curse.pause)
			curse_clear_scvs(&vm->curse);
		vm->curse.pause = 1 - vm->curse.pause;
	}
	else if (key == KEY_ESCAPE)
	{
		endwin();
		system("killall afplay 2&>/dev/null >/dev/null");
		call_zerglings(vm->scv);
		exit(0);
	}
	return (key);
}

static void	maelstrom(t_vm *vm)
{
	if (vm->flags & F_VISUAL)
	{
		usleep(200000 - vm->curse.speed * 20000);
		while (!user_input(vm) || vm->curse.pause)
			;
	}
}

static void	game_init(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	init_scv(vm);
	if (vm->flags & F_VISUAL)
	{
		curse_init(&vm->curse);
		curse_memory(vm);
		curse_players(vm, 0, -1);
	}
}

void		gl_hf(t_vm *vm)
{
	game_init(vm);
	while (vm->scv)
	{
		maelstrom(vm);
		if (vm->flags & F_DUMP && vm->cycle == vm->dump)
			break ;
		if (!(vm->cycle % vm->dump))
		{
			if (vm->flags & F_VISUAL)
				curse_memory(vm);
			else if (vm->flags & F_DUMP_FREQUENCY)
				dump_memory(vm);
		}
		get_scv_redcode(vm, &vm->scv);
		if (!vm->cycle_to_die--)
			reset_cycle(vm);
		++vm->cycle;
	}
	curse_players(vm, 1, -1);
	vm->curse.pause = 1;
	maelstrom(vm);
}
