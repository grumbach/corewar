/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_ncurse2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 20:33:10 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/24 02:18:50 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			curse_color(t_vm *vm, int pc, int color)
{
	wattron(vm->curse.wmem, COLOR_PAIR(color));
	mvwprintw(vm->curse.wmem, 3 + pc / vm->curse.n, 1 + \
		(pc % vm->curse.n) * 3, "%02x", vm->memory[pc % MEM_SIZE]);
	wattroff(vm->curse.wmem, COLOR_PAIR(color));
	if (!(vm->cycle % vm->dump))
		wrefresh(vm->curse.wmem);
}

static void		curse_init_colors(void)
{
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_1, COLOR_BLACK);
	init_pair(3, COLOR_1L, COLOR_BLACK);
	init_pair(4, COLOR_1, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_1);
	init_pair(6, COLOR_2, COLOR_BLACK);
	init_pair(7, COLOR_2L, COLOR_BLACK);
	init_pair(8, COLOR_2, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_2);
	init_pair(10, COLOR_3, COLOR_BLACK);
	init_pair(11, COLOR_3L, COLOR_BLACK);
	init_pair(12, COLOR_3, COLOR_WHITE);
	init_pair(13, COLOR_BLACK, COLOR_3);
	init_pair(14, COLOR_4, COLOR_BLACK);
	init_pair(15, COLOR_4L, COLOR_BLACK);
	init_pair(16, COLOR_4, COLOR_WHITE);
	init_pair(17, COLOR_BLACK, COLOR_4);
	init_pair(18, COLOR_YELLOW, COLOR_YELLOW);
}

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

static void		curse_boxes(t_curse *curse)
{
	wattron(curse->wmem, COLOR_PAIR(14));
	box(curse->wmem, '|', '=');
	wattroff(curse->wmem, COLOR_PAIR(14));
	wattron(curse->wscv, COLOR_PAIR(14));
	box(curse->wscv, '|', '=');
	wattroff(curse->wscv, COLOR_PAIR(14));
	wattron(curse->wlog, COLOR_PAIR(14));
	box(curse->wlog, '|', '=');
	wattroff(curse->wlog, COLOR_PAIR(14));
	wrefresh(curse->wmem);
	wrefresh(curse->wscv);
	wrefresh(curse->wlog);
}

void			curse_init(t_curse *curse)
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
	curse->speed = DEFAULT_SPEED;
	curse->pause = 1;
	curse->wmem = newwin(MEM_SIZE / curse->n + 4, curse->n * 3 + 1, 0, 0);
	curse->wscv = newwin(curse->y, curse->x - curse->n * 3 - 1, 0, \
		curse->n * 3 + 1);
	curse->wlog = newwin(curse->y - MEM_SIZE / curse->n - 4, \
		curse->n * 3 + 1, MEM_SIZE / curse->n + 4, 0);
	curse_init_colors();
	curse_boxes(curse);
	cbreak();
	noecho();
	nodelay(curse->wmem, TRUE);
	curs_set(0);
}

void			curse_players(t_vm *vm, int end, int i)
{
	curse_clear_scvs(&vm->curse);
	while (++i < vm->nb_players)
		if ((end && vm->core[i].id == vm->last_id_alive) || \
			(!end))
		{
			wattron(vm->curse.wscv, COLOR_PAIR(vm->core[i].color));
			if (end)
				mvwprintw(vm->curse.wscv, 1, 4, "Glory and Kittens to:");
			mvwprintw(vm->curse.wscv, 3 + i * 6 * !end, 4, \
				"Name    %s", vm->core[i].prog_name);
			mvwprintw(vm->curse.wscv, 4 + i * 6 * !end, 4, \
				"ID      %d", vm->core[i].id);
			mvwprintw(vm->curse.wscv, 5 + i * 6 * !end, 4, \
				"Weight  %d", vm->core[i].prog_size);
			mvwprintw(vm->curse.wscv, 6 + i * 6 * !end, 4, \
				"Comment %s", vm->core[i].comment);
			mvwprintw(vm->curse.wscv, 7 + i * 6 * !end, 4, \
				"Cycle   %d", vm->cycle);
			wattroff(vm->curse.wscv, COLOR_PAIR(vm->core[i].color));
			if (end)
				break ;
		}
	if (i == vm->nb_players && end)
		mvwprintw(vm->curse.wscv, 1, 4, "What a bunch of loosers...");
	wrefresh(vm->curse.wscv);
}
