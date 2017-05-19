/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_ncurse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 20:33:10 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/19 20:36:58 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** function to display messages and aff inside the log window
*/

void		curse_puts_log(t_vm *vm, t_scv *scv, char *s)
{
	static int	y[MAX_PLAYERS] = {0, 0, 0, 0};
	static int	x[MAX_PLAYERS] = {0, 0, 0, 0};
	const int	i = (scv->color - 2) / 3;

	if (!(vm->flags & F_VISUAL))
		return ;
	if (x[i] + (int)ft_strlen(s) > (vm->curse.n * 3 - 3) / \
		vm->nb_players && ++y[i])
		x[i] = 0;
	if (y[i] > 13)
	{
		y[i] = 0;
		while (y[i] < 13)
			curse_puts_log(vm, scv, " ");
		y[i] = 0;
	}
	wmove(vm->curse.wlog, 1 + y[i], 1 + \
	x[i] + (i) * (vm->curse.n * 3 - 3) / vm->nb_players);
	wattron(vm->curse.wlog, COLOR_PAIR(scv->color));
	wprintw(vm->curse.wlog, s);
	wattroff(vm->curse.wlog, COLOR_PAIR(scv->color));
	x[i] += ft_strlen(s);
	if (ft_strchr(s, '!') && ++y[i])
		x[i] = 0;
	wrefresh(vm->curse.wlog);
}

void		curse_color(t_vm *vm, int pc, int color)
{
	wattron(vm->curse.wmem, COLOR_PAIR(color));
	mvwprintw(vm->curse.wmem, 3 + pc / vm->curse.n, 1 + \
		(pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
	wattroff(vm->curse.wmem, COLOR_PAIR(color));
	if (!(vm->flags & F_DUMP_FREQUENCY)
		|| !(vm->cycle % vm->bonus.dump_frequency))
		wrefresh(vm->curse.wmem);
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
	box(curse->wmem, '|', '=');
	wattroff(curse->wmem, COLOR_PAIR(11));
	wattron(curse->wscv, COLOR_PAIR(11));
	box(curse->wscv, '|', '=');
	wattroff(curse->wscv, COLOR_PAIR(11));
	wattron(curse->wlog, COLOR_PAIR(11));
	box(curse->wlog, '|', '=');
	wattroff(curse->wlog, COLOR_PAIR(11));
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
	curse->speed = DEFAULT_SPEED;
	curse->pause = 1;
	curse->wmem = newwin(MEM_SIZE / curse->n + 4, curse->n * 3 + 1, 0, 0);
	curse->wscv = newwin(curse->y, curse->x - curse->n * 3 - 1, 0, \
		curse->n * 3 + 1);
	curse->wlog = newwin(curse->y - MEM_SIZE / curse->n - 4, \
		curse->n * 3 + 1, MEM_SIZE / curse->n + 4, 0);
	curse_init_colors(curse);
	wrefresh(curse->wmem);
	wrefresh(curse->wscv);
	wrefresh(curse->wlog);
	cbreak();
	noecho();
	nodelay(curse->wmem, TRUE);
}
