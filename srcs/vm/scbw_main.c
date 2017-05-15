/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 00:53:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/15 11:43:40 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** check verbose mode with : ./corewar -v 31 ../warriors/helltrain.cor > test
*/

void		init_rc(t_vm *vm)
{
	const t_rc	rc[17] = \
	{
		{NULL, 0, {0}, 0, 0, 0},
		{&rc_live, 1, {T_DIR}, 10, 0, 4},
		{&rc_ld, 2, {T_DIR | T_IND, T_REG}, 5, 1, 4},
		{&rc_st, 2, {T_REG, T_IND | T_REG}, 5, 1, 0},
		{&rc_add, 3, {T_REG, T_REG, T_REG}, 10, 1, 0},
		{&rc_sub, 3, {T_REG, T_REG, T_REG}, 10, 1, 0},
		{&rc_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
		{&rc_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
		{&rc_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
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

int			main(int ac, char **av)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	init_rc(&vm);
	vm.dump = -1;
	parsing(ac, av, &vm, 0);
	if (!(vm.flags & F_VISUAL))
		vm.flags |= F_MUTE;
	if (vm.nb_players)
		init_cores(&vm, 0);
	else
		errors(1, "this memory is sad and lonely");
	if (!(vm.flags & F_MUTE))
		play_music();
	gl_hf(&vm);
	if (vm.flags & F_VISUAL)
	{
		delwin(vm.curse.win);
		endwin();
	}
	if (vm.dump != -1)
		dump_memory(&vm);
	call_zerglings(vm.scv);
	display_winner(&vm);
	system("killall afplay 2&>/dev/null >/dev/null");
	return (0);
}

/*
** error handler
*/

long			errors(int id, char *comment)
{
	ft_putstr_fd("corewar: ", 2);
	if (comment)
		ft_putendl_fd(comment, 2);
	if (id == 0)
		ft_putendl_fd(strerror(errno), 2);
	if (id == 2)
		ft_putstr_fd("usage: ./corewar [-"COREWAR_FLAGS"] "
		"[-dump cyclecount] [-n id champ] [champs ...]\n"
		"  -m : mute\n  -v : vizualizer\n", 2);
	if (id == 3)
		ft_putstr_fd("Name is too big give it up\n", 2);
	if (id == 4)
		ft_putstr_fd("\nPS: Any sufficiently advanced technology is"
		"indistinguishable from magic\n", 2);
	exit(1);
}

/*
** 0x01 rc_live : The instruction that allows a scv to stay alive.
** It can also record that the player whose number is the argument is indeed
** alive. Its argument is on 4 bytes
**
** 0x02 rc_ld : Take a random argument and a registry. Load the value of the 1st
** argument in the registry and will change the carry.
**
** 0x0d rc_lld : Means long-load. It the same as ld, but without % IDX_MOD.
** Modify the carry.
**
** 0x03 rc_st : take a registry and (a registry || an indirect) and
** store the value of the registry toward a second argument.
** ie : st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
**
** 0x0b rc_sti : Take a registry, and two indexes (potentially registries),
** add the two indexes, and use this result as an address where the value of
** the first parameter will be copied.
**
** 0x04 rc_add : Take 3 registries, add the first two, and place the result
** in the 3d, right before modifying the carry.
**
** 0x05 rc_sub : same as add but with a substraction.
**
** rc_add_sub(vm, scv, 9 - (redcode << 1)); if 0x04 we get 1, if 0x05 we get -1
**
** 0x06 rc_and : Apply an & (bit-to-bit AND) over the first two arguments and
** store the result in a registry, which is the 3d argument. Modifies the carry
**
** 0x07 rc_or : This operation is an bit-to-bit OR.
**
** 0x08 rc_xor : Acts like and with an exclusive OR.
**
** 0x09 rc_zjmp : No argument’s coding byte behind this operation.
** It will take an index and jump to this address if the carry is 1.
**
** 0x0a rc_ldi : ldi will use 2 indexes and 1 registry, adding the first
** two, treating that like an address, reading a value of a registry’s size
** and putting it on the third.
**
** 0x0e rc_lldi : Same as ldi, but does not apply any modulo to the addresses.
** It will however, modify the carry
**
** 0x0c rc_fork : no argument’s coding byte, take an index. Create a
** new scv that will inherit the different states of its father, except its PC,
** which will be put at (PC + (1st parameter % IDX_MOD)).
**
** 0x0f rc_lfork : long-fork. Same as a fork without modulo in the address.
**
** 0x10 rc_aff : There is an argument’s coding byte which is a registry,
** and its content is interpreted by the character’s ASCII value
** to display on the standard output. The code is modulo 256
**
** !!!!!!!!!!!!!! scv->cooldown = rc[redcode].cooldown;
** !!!!!!! RENAME scv -> SCV
**
*/

/*
**.
** t_op    op_tab[17] =
** {
**   {0, 0, {0}, 0, 0, 0, 0, 0}
** 	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
** 	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
** 	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
** 	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
** 	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
** 	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
** 		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
** 	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
** 		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
** 	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
** 		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
** 	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
** 	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
** 		"load index", 1, 1},
** 	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
** 		"store index", 1, 1},
** 	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
** 	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
** 	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
** 		"long load index", 1, 1},
** 	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
** 	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
**.
** };
*/
