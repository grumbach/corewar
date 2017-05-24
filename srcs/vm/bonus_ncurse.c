/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_ncurse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:16:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/24 06:55:07 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	curse_reg(WINDOW *win, uint reg[REG_NUMBER + 1], int i)
{
	uint	index;
	int		y;
	int		x;

	index = 0;
	while (++index <= REG_NUMBER)
	{
		y = 3 + i % 16 * 5;
		x = 20 + index * 3 + ((i >> 4) * 96);
		mvwprintw(win, y, x, "%02x", (reg[index] >> 24) & 0xff);
		mvwprintw(win, 1 + y, x, "%02x", (reg[index] >> 16) & 0xff);
		mvwprintw(win, 2 + y, x, "%02x", (reg[index] >> 8) & 0xff);
		mvwprintw(win, 3 + y, x, "%02x", reg[index] & 0xff);
	}
}

static void	curse_scv(WINDOW *win, t_scv *scv)
{
	t_scv	*scv_lst;
	int		i;
	int		x;
	int		y;

	wattron(win, COLOR_PAIR(14));
	mvwprintw(win, 1, 2, \
	"[SCVs]  {registries} 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16");
	wattroff(win, COLOR_PAIR(14));
	scv_lst = scv;
	i = 0;
	while (scv_lst && i < 15)
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
	wattron(vm->curse.wmem, COLOR_PAIR(14));
	mvwprintw(vm->curse.wmem, 1, 2, "Current Cycle : % 6d", vm->cycle);
	mvwprintw(vm->curse.wmem, 1, 30, "Cycles to Die : % 6d", vm->cycle_to_die);
	mvwprintw(vm->curse.wmem, 1, 60, "SCVs Alive : % 6d", vm->nb_scv);
	mvwprintw(vm->curse.wmem, 1, 90, "Total Lives : % 6d", vm->nb_total_live);
	mvwprintw(vm->curse.wmem, 1, 120, "Last Live : % 4d", vm->last_id_alive);
	mvwprintw(vm->curse.wmem, 1, 169, "Game Speed : %02d [+] [-]", \
		vm->curse.speed);
	wattroff(vm->curse.wmem, COLOR_PAIR(14));
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
	if (!(vm->cycle % vm->dump))
	{
		pc = 0;
		while (pc < MEM_SIZE)
		{
			wattron(vm->curse.wmem, COLOR_PAIR(vm->creep[pc]));
			mvwprintw(vm->curse.wmem, 3 + pc / vm->curse.n, \
				1 + (pc % vm->curse.n) * 3, "%02x", \
			!(vm->flags & F_STEALTH) ? vm->memory[pc] : 0xff);
			wattroff(vm->curse.wmem, COLOR_PAIR(vm->creep[pc]));
			++pc;
		}
		wrefresh(vm->curse.wmem);
		curse_scv(vm->curse.wscv, vm->scv);
	}
}

void		curse_clear_scvs(t_curse *curse)
{
	werase(curse->wscv);
	wattron(curse->wscv, COLOR_PAIR(14));
	box(curse->wscv, '|', '=');
	wattroff(curse->wscv, COLOR_PAIR(14));
	wrefresh(curse->wscv);
}
