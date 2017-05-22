/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 00:53:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/22 07:10:57 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

long		errors(int id, char *comment)
{
	ft_putstr_fd("corewar: ", 2);
	if (comment)
		ft_putendl_fd(comment, 2);
	if (id == 0)
		ft_putendl_fd(strerror(errno), 2);
	if (id == 2)
		ft_putstr_fd("usage: ./corewar [-"COREWAR_FLAGS"] "
		"[-dump cyclecount] [-n id champ] [champs ...]\n"
		"  -m	 Mute all sound\n"
		"  -v	 Vizualizer\n"
		"  -l	 Display logs (including redcode 0x10) (hidden by default)\n"
		"  -s	 Stealth mode (hide memory content)\n"
		"  -D[x]	 Dump memory every x cycle\n", 2);
	if (id == 3)
		ft_putstr_fd("Name is too big give it up\n", 2);
	if (id == 4)
		ft_putstr_fd("\nPS: Any sufficiently advanced technology is"
		" indistinguishable from magic\n", 2);
	exit(1);
}

static void	init_rc(t_vm *vm)
{
	vm->rc[0] = (t_rc){NULL, 0, {0}, 0, 0, 0};
	vm->rc[LIVE] = (t_rc){&rc_live, 1, {T_DIR}, 10, 0, 4};
	vm->rc[LD] = (t_rc){&rc_ld, 2, {T_DIR | T_IND, T_REG}, 5, 1, 4};
	vm->rc[ST] = (t_rc){&rc_st, 2, {T_REG, T_IND | T_REG}, 5, 1, 0};
	vm->rc[ADD] = (t_rc){&rc_add, 3, {T_REG, T_REG, T_REG}, 10, 1, 0};
	vm->rc[SUB] = (t_rc){&rc_sub, 3, {T_REG, T_REG, T_REG}, 10, 1, 0};
	vm->rc[AND] = (t_rc){&rc_and, 3, \
		{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4};
	vm->rc[OR] = (t_rc){&rc_or, 3, \
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4};
	vm->rc[XOR] = (t_rc){&rc_xor, 3, \
		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4};
	vm->rc[ZJMP] = (t_rc){&rc_zjmp, 1, {T_DIR}, 20, 0, 2};
	vm->rc[LDI] = (t_rc){&rc_ldi, 3, \
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2};
	vm->rc[STI] = (t_rc){&rc_sti, 3, \
		{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2};
	vm->rc[FORK] = (t_rc){&rc_fork, 1, {T_DIR}, 800, 0, 2};
	vm->rc[LLD] = (t_rc){&rc_lld, 2, {T_DIR | T_IND, T_REG}, 10, 1, 4};
	vm->rc[LLDI] = (t_rc){&rc_lldi, 3, \
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 2};
	vm->rc[LFORK] = (t_rc){&rc_lfork, 1, {T_DIR}, 1000, 0, 2};
	vm->rc[AFF] = (t_rc){&rc_aff, 1, {T_REG}, 2, 1, 0};
}

static uint	init_cores(const int fd, t_vm *vm, int i)
{
	uint	magic;

	vm->core[i].color = (i << 2) + 2;
	if (-1 == read(fd, &magic, 4))
		errors(0, 0);
	if (endianize(magic) != COREWAR_EXEC_MAGIC)
	{
		close(fd);
		errors(4, "why not 0xea83f3 ?");
	}
	if (-1 == read(fd, &vm->core[i].prog_name, PROG_NAME_LENGTH))
		errors(0, 0);
	if (-1 == lseek(fd, 0x04, SEEK_CUR))
		errors(0, 0);
	if (-1 == read(fd, &vm->core[i].prog_size, 4))
		errors(0, 0);
	if (!vm->core[i].prog_size)
		errors(1, "just show me the code!");
	if (-1 == read(fd, &vm->core[i].comment, COMMENT_LENGTH))
		errors(0, 0);
	vm->core[i].prog_size = endianize(vm->core[i].prog_size);
	return (magic);
}

static void	init_game(t_vm *vm)
{
	int		i;
	int		fd;
	uint	magic;
	int		pos;

	i = 0;
	while (i < vm->nb_players)
	{
		if ((fd = open(vm->core[i].prog_name, O_RDONLY)) < 0)
			errors(0, vm->core[i].prog_name);
		pos = i * (MEM_SIZE / vm->nb_players);
		magic = init_cores(fd, vm, i);
		if (-1 == read(fd, &(vm->memory[pos]), vm->core[i].prog_size))
			errors(0, 0);
		ft_memset(&(vm->creep[pos]), vm->core[i].color, vm->core[i].prog_size);
		close(fd);
		if (vm->core[i].prog_size > CHAMP_MAX_SIZE)
			errors(1, "way.... too... much.. code.");
		++i;
	}
}

int			main(int ac, char **av)
{
	t_vm		vm;

	ft_bzero(&vm, sizeof(vm));
	init_rc(&vm);
	vm.dump = 1;
	parsing(ac, av, &vm, 0);
	if (!(vm.flags & F_VISUAL))
		vm.flags |= F_MUTE;
	vm.nb_players ? init_game(&vm) : \
		errors(1, "this memory is sad and lonely");
	if (!(vm.flags & F_MUTE))
		play_music();
	gl_hf(&vm);
	if (vm.flags & F_VISUAL)
		endwin();
	if (vm.flags & F_DUMP)
		dump_memory(&vm);
	else if (!(vm.flags & F_VISUAL))
		display_winner(&vm);
	call_zerglings(vm.scv);
	system("killall afplay 2&>/dev/null >/dev/null");
	return (0);
}
