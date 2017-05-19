/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_ncurse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:16:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/19 20:39:13 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	curse_reg(WINDOW *win, uint reg[REG_NUMBER + 1], int i)
{
	uint		x;

	x = 0;
	while (++x <= REG_NUMBER)
	{
		mvwprintw(win, 3 + i % 16 * 5, 20 + x * 3 + ((i >> 4) * 96), \
		"%02x", (reg[x] >> 6) & 0xff);
		mvwprintw(win, 4 + i % 16 * 5, 20 + x * 3 + ((i >> 4) * 96), \
		"%02x", (reg[x] >> 4) & 0x00ff);
		mvwprintw(win, 5 + i % 16 * 5, 20 + x * 3 + ((i >> 4) * 96), \
		"%02x", (reg[x] >> 2) & 0x0000ff);
		mvwprintw(win, 6 + i % 16 * 5, 20 + x * 3 + ((i >> 4) * 96), \
		"%02x", reg[x] & 0xff);
	}
}

static void	curse_scv(WINDOW *win, t_scv *scv)
{
	t_scv	*scv_lst;
	int		i;
	int		x;
	int		y;

	wattron(win, COLOR_PAIR(11));
	mvwprintw(win, 1, 2, \
	"[SCVs]  {registries} 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16");
	wattroff(win, COLOR_PAIR(11));
	scv_lst = scv;
	i = 0;
	while (scv_lst && i < 32)
	{
		y = i % 16 * 5;
		x = 2 + ((i >> 4) * 96);
		wattron(win, COLOR_PAIR(scv_lst->color));
		mvwprintw(win, 3 + y, x, "pc       % 6u", scv_lst->pc);
		mvwprintw(win, 4 + y, x, "cooldown % 6u", scv_lst->cooldown);
		mvwprintw(win, 5 + y, x, "carry    % 6u", scv_lst->carry);
		mvwprintw(win, 6 + y, x, "live     % 6u", scv_lst->live);
		curse_reg(win, scv_lst->reg, i++);
		wattroff(win, COLOR_PAIR(scv_lst->color));
		scv_lst = scv_lst->next;
	}
	wrefresh(win);
}

static void	curse_menu(t_vm *vm)
{
	wattron(vm->curse.wmem, COLOR_PAIR(11));
	mvwprintw(vm->curse.wmem, 1, 2, "Current Cycle : % 6d", vm->cycle);
	mvwprintw(vm->curse.wmem, 1, 30, "Cycles to Die : % 6d", vm->cycle_to_die);
	mvwprintw(vm->curse.wmem, 1, 60, "SCVs Alive : % 6d", vm->nb_scv);
	mvwprintw(vm->curse.wmem, 1, 90, "Total Lives : % 6d", vm->nb_total_live);
	mvwprintw(vm->curse.wmem, 1, 120, "Last Live : % 4d", vm->last_id_alive);
	mvwprintw(vm->curse.wmem, 1, 169, "Game Speed : %02d [+] [-]", \
		vm->curse.speed);
	wattroff(vm->curse.wmem, COLOR_PAIR(11));
	wrefresh(vm->curse.wmem);
}

/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void		curse_memory(t_vm *vm)
{
	size_t	pc;

	curse_menu(vm);
	if (!(vm->cycle % vm->bonus.dump_frequency))
	{
		pc = 0;
		wattron(vm->curse.wmem, COLOR_PAIR(vm->creep[pc]));
		while (pc < MEM_SIZE)
		{
			mvwprintw(vm->curse.wmem, 3 + pc / vm->curse.n, \
				1 + (pc % vm->curse.n) * 3, "%02x", \
			!(vm->flags & F_STEALTH) ? vm->memory[pc] : 0xff);
			++pc;
		}
		wattroff(vm->curse.wmem, COLOR_PAIR(vm->creep[pc]));
		wrefresh(vm->curse.wmem);
		curse_scv(vm->curse.wscv, vm->scv);
	}
}

void		curse_clear_scvs(t_curse *curse)
{
	werase(curse->wscv);
	wattron(curse->wscv, COLOR_PAIR(11));
	box(curse->wscv, '|', '=');
	wattroff(curse->wscv, COLOR_PAIR(11));
	wrefresh(curse->wscv);
}

/*
** display player info

static void	curse_players(t_vm *vm)//disp player info right of mem at start
{
	int	i;
	int	offset;

	i = 0;
	offset = 240;
	mvwprintw(vm->curse.win, 20, offset, "Our Gladiators, Ave Caesar, Morituri te salutant :");
	while (i < vm->nb_players)
	{
		mvwprintw(vm->curse.win, 22 + i * 5, offset, "\tPlayer %d : %s", vm->core[i].id, vm->core[i].prog_name);
		mvwprintw(vm->curse.win, 23 + i * 5, offset, "\tComment : %s", vm->core[i].comment);
		mvwprintw(vm->curse.win, 24 + i * 5, offset, "\tWeight : %X", vm->core[i].prog_size);
		++i;
	}
	wrefresh(vm->curse.win);
}*/
