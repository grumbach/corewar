/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_ncurse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:16:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/17 05:24:24 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			curse_puts_log(t_vm *vm, t_scv *scv, char *s)
{
	static int	y[MAX_PLAYERS] = {0, 0, 0, 0};
	static int	x[MAX_PLAYERS] = {0, 0, 0, 0};
	const int	i = (scv->color - 2) / 3;

	if (x[i] + (int)ft_strlen(s) > 186 / vm->nb_players && ++y[i])
		x[i] = 0;
	wmove(vm->curse.wlog, 1 + y[i], 2 + \
	x[i] + (i) * 190 / vm->nb_players);
	wattron(vm->curse.wlog, COLOR_PAIR(scv->color));
	wprintw(vm->curse.wlog, s);
	wattroff(vm->curse.wlog, COLOR_PAIR(scv->color));
	x[i] += ft_strlen(s);
	if (ft_strchr(s, '!') && ++y[i])
		x[i] = 0;
	if (y[i] > 15)
	{
		y[i] = 0;
		while (y[i] < 15)
			curse_puts_log(vm, scv, " ");
		y[i] = 0;
	}
	wrefresh(vm->curse.wlog);
}

void		curse_color(t_vm *vm, int pc, int color)
{
	wattron(vm->curse.wmem, COLOR_PAIR(color));
	mvwprintw(vm->curse.wmem, 3 + pc / vm->curse.n, 1 + \
		(pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
	wattroff(vm->curse.wmem, COLOR_PAIR(color));
	wrefresh(vm->curse.wmem);
}

static void	curse_reg(WINDOW *win, uint reg[REG_NUMBER + 1], int i)
{
	uint		x;

	x = 0;
	while (++x <= REG_NUMBER)
	{
		mvwprintw(win, 3 + i * 5, 20 + x * 3, "%02x", (reg[x] >> 6) & 0xff);
		mvwprintw(win, 4 + i * 5, 20 + x * 3, "%02x", (reg[x] >> 4) & 0xff);
		mvwprintw(win, 5 + i * 5, 20 + x * 3, "%02x", (reg[x] >> 2) & 0xff);
		mvwprintw(win, 6 + i * 5, 20 + x * 3, "%02x", reg[x] & 0xff);
	}
}

static void	curse_scv(WINDOW *win, t_scv *scv)
{
    t_scv   *scv_lst;
    int     i;

    i = 0;
	wattron(win, COLOR_PAIR(11));
	mvwprintw(win, 1, 2, \
		"[SCVs]  {registries} 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16");
	wattroff(win, COLOR_PAIR(11));
	scv_lst = scv;
	while (scv_lst)
	{
		if (i < 16)
		{
			wattron(win, COLOR_PAIR(scv_lst->color));
			mvwprintw(win, 3 + i * 5, 2, "pc       % 6u", scv_lst->pc);
			mvwprintw(win, 4 + i * 5, 2, "cooldown % 6u", scv_lst->cooldown);
			mvwprintw(win, 5 + i * 5, 2, "carry    % 6u", scv_lst->carry);
			mvwprintw(win, 6 + i * 5, 2, "live     % 6u", scv_lst->live);
			curse_reg(win, scv_lst->reg, i);
			wattroff(win, COLOR_PAIR(scv_lst->color));
			++i;
		}
		scv_lst = scv_lst->next;
	}
	wrefresh(win);
}

/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void    curse_memory(t_vm *vm)
{
	size_t	pc;

	wattron(vm->curse.wmem, COLOR_PAIR(11));
	mvwprintw(vm->curse.wmem, 1, 2, "Current Cycle : % 6d", vm->cycle);
	mvwprintw(vm->curse.wmem, 1, 30, "Cycles to Die : % 6d", vm->cycle_to_die);
	mvwprintw(vm->curse.wmem, 1, 60, "SCVs Alive : % 6d", vm->nb_scv);
	mvwprintw(vm->curse.wmem, 1, 90, "Total Lives : % 6d", vm->nb_total_live);
	mvwprintw(vm->curse.wmem, 1, 120, "Last Live : % 4d", vm->last_id_alive);
	mvwprintw(vm->curse.wmem, 1, 169, "Game Speed : %02d [+] [-]", \
		vm->curse.speed);
	wattroff(vm->curse.wmem, COLOR_PAIR(11));
	pc = 0;
	while (pc < MEM_SIZE)
	{
		wattron(vm->curse.wmem, COLOR_PAIR(vm->creep[pc]));
		mvwprintw(vm->curse.wmem, 3 + pc / vm->curse.n, 1 + \
			(pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
		wattroff(vm->curse.wmem, COLOR_PAIR(vm->creep[pc]));
		++pc;
	}
	wrefresh(vm->curse.wmem);
	curse_scv(vm->curse.wscv, vm->scv);
}

static void	curse_init_colors(t_curse *curse)
{
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_1, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_1);
	init_pair(4, COLOR_WHITE, COLOR_1);
    init_pair(5, COLOR_2, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_2);
	init_pair(7, COLOR_WHITE, COLOR_2);
	init_pair(8, COLOR_3, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_3);
	init_pair(10, COLOR_WHITE, COLOR_3);
	init_pair(11, COLOR_4, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_4);
	init_pair(13, COLOR_WHITE, COLOR_4);
	init_pair(14, COLOR_YELLOW, COLOR_YELLOW);
	wattron(curse->wmem, COLOR_PAIR(11));
	box(curse->wmem, '|' , '=');
	wattroff(curse->wmem, COLOR_PAIR(11));
	wattron(curse->wscv, COLOR_PAIR(11));
	box(curse->wscv, '|' , '=');
	wattroff(curse->wscv, COLOR_PAIR(11));
	wattron(curse->wlog, COLOR_PAIR(11));
	box(curse->wlog, '|' , '=');
	wattroff(curse->wlog, COLOR_PAIR(11));
}

void		curse_init(t_curse *curse)
{
    int		i;

	initscr();
    getmaxyx(stdscr, curse->y, curse->x);
	curse->n = curse->x / 3;
	i = 1;
	while (i < curse->n)
    	i <<= 1;
	if ((curse->n = i >> 1) < 1)
		curse->n = 4;
	curse->speed = 2;
	curse->pause = 1;
	curse->wmem = newwin(MEM_SIZE / curse->n + 4, curse->n * 3 + 1, 0, 0);
	curse->wscv = newwin(curse->y, curse->x - curse->n * 3 - 1, 0, curse->n * 3 + 1);
	curse->wlog = newwin(curse->y - MEM_SIZE / curse->n - 4, curse->n * 3 + 1, MEM_SIZE / curse->n + 4, 0);
	curse_init_colors(curse);
	wrefresh(curse->wmem);
	wrefresh(curse->wscv);
	wrefresh(curse->wlog);
	cbreak();
	noecho();
	nodelay(curse->wmem, TRUE);
}

void		curse_clear_scvs(t_curse *curse)
{
	werase(curse->wscv);
	wattron(curse->wscv, COLOR_PAIR(11));
	box(curse->wscv, '|' , '=');
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

/*
** Initialize the window
**
** getmaxyx(stdscr, row, col); find the boundaries of the screeen
**
** noecho(); -> Don't echo any keypresses
** https://linux.die.net/man/3/init_color
** The init_pair routine changes the definition of a color-pair. It takes three
** arguments: the number of the color-pair to be changed, the foreground color
** number, and the background color number
**
** The init_color routine changes the definition of a color. It takes 4 args:
** the number of the color to be changed followed by three RGB values.
** The value of the first argument must be between 0 and COLORS.
** (See the section Colors for the default color index.)
** Each of the last three arguments must be a value between 0 and 1000.
** When init_color is used, all occurrences of that color on the screen
** immediately change to the new definition.
** curs_set(0) hide cursor
** nodelay is to be able to user key hook without waiting for user input
*/



/*
void		bsw(unsigned char b)//
{
	int		a[4];
	char	*s[4] = {"IND", "DIR", "REG", "..."};

	a[0] = b >> 6;
	a[1] = (b >> 4) & 3;
	a[2] = (b>> 2) & 3;
	a[3] = b & 3;

    move(68, 0);
	printw("--------------------------\n");
    printw("Base 02 ~ %d %d %d %d", a[0] / 2, a[1] / 2, a[2] / 2, a[3] / 2);//
	printw("  >>>  %s %s %s %s\n", s[0], s[1], s[2], s[3]);
	printw("Hexa 16 ~ %#11x\nBase 10 ~ %11d\n------------------------\n", b, b);
}
*/
