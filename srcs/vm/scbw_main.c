/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 00:53:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/20 00:16:50 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** check verbose mode with : ./corewar -v 31 ../warriors/helltrain.cor > test
*/

void	init_rc(t_vm *vm)
{
	const t_rc	rc[17] = {{NULL, 0, {0}, 0, 0, 0},
		{&rc_live, 1, {T_DIR}, 10, 0, 4},
		{&rc_ld, 2, {T_DIR | T_IND, T_REG}, 5, 1, 4},
		{&rc_st, 2, {T_REG, T_IND | T_REG}, 5, 1, 0},
		{&rc_add, 3, {T_REG, T_REG, T_REG}, 10, 1, 0},
		{&rc_sub, 3, {T_REG, T_REG, T_REG}, 10, 1, 0},
		{&rc_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, \
			6, 1, 4},
		{&rc_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, \
			6, 1, 4},
		{&rc_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, \
			6, 1, 4},
		{&rc_zjmp, 1, {T_DIR}, 20, 0, 2},
		{&rc_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2},
		{&rc_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2},
		{&rc_fork, 1, {T_DIR}, 800, 0, 2},
		{&rc_lld, 2, {T_DIR | T_IND, T_REG}, 10, 1, 2},
		{&rc_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 4},
		{&rc_lfork, 1, {T_DIR}, 1000, 0, 2},
		{&rc_aff, 1, {T_REG}, 2, 1, 2}
	};
	ft_memcpy(vm->rc, rc, sizeof(rc));
}

/*
** if not parsed, dump will be initialized at -1 instead of 0.
** dump is used to display memory at the dump cycle
*/

int		main(int ac, char **av)
{
	t_vm		vm;

	ft_bzero(&vm, sizeof(vm));
	init_rc(&vm);
	vm.dump = 1;
	parsing(ac, av, &vm, 0);
	if (!(vm.flags & F_VISUAL))
		vm.flags |= F_MUTE;
	vm.nb_players ? init_cores(&vm, 0) : \
		errors(1, "this memory is sad and lonely");
	if (!(vm.flags & F_MUTE))
		play_music();
	gl_hf(&vm);
	if (vm.flags & F_VISUAL)
		endwin();
	if (vm.flags & F_DUMP)
		dump_memory(&vm);
	call_zerglings(vm.scv);
	if (!(vm.flags & F_VISUAL))
		display_winner(&vm);
	system("killall afplay 2&>/dev/null >/dev/null");
	return (0);
}

/*
** error handler
*/

long	errors(int id, char *comment)
{
	ft_putstr_fd("corewar: ", 2);
	if (comment)
		ft_putendl_fd(comment, 2);
	if (id == 0)
		ft_putendl_fd(strerror(errno), 2);
	if (id == 2)
		ft_putstr_fd("usage: ./corewar [-"COREWAR_FLAGS"] "
		"  -m : Mute\n"
		"  -v : Vizualizer Ncurses\n"
		"  -a : Display 0x10 aff redcode (hidden by default)\n"
		"  -s : Stealth mode (no clue about what is read in the memory)\n"
		"  -Dx : Dump memory every x cycle\n"
		"[-dump cyclecount] [-n id champ] [champs ...]\n"
		"example : make && ./corewar -vmsD500 -dump 2500 warriors/zork.cor", 2);
	if (id == 3)
		ft_putstr_fd("Name is too big give it up\n", 2);
	if (id == 4)
		ft_putstr_fd("\nPS: Any sufficiently advanced technology is"
		" indistinguishable from magic\n", 2);
	exit(1);
}
