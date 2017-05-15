/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_ncurse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:16:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/15 13:10:17 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			curse_putchar_log(uint c)
{
	ft_putchar(c);//TODO!!
}

void			curse_putstr_log(char *s)
{
	ft_putstr(s);//TODO!!
}

static void		curse_frame(WINDOW *win, int y, int x, int n)
{
	int		i;

	wattron(win, COLOR_PAIR(11));
	mvwprintw(win, 0, 0, "+");
	mvwprintw(win, y - 1, 0, "+");
	mvwprintw(win, 0, x - 1, "+");
	mvwprintw(win, y - 1, x - 1, "+");
	i = 0;
	while (++i < y - 1)
	{
		mvwprintw(win, i, 0, "|");
		mvwprintw(win, i, x - 1, "|");
	}
	i = 0;
	while (++i < x - 1)
	{
		mvwprintw(win, 0, i, "-");
		mvwprintw(win, y - 1, i, "-");
		mvwprintw(win, 3 + MEM_SIZE / n, (i < n * 3 ? i : 3), "-");
	}
	i = 0;
	while (++i < y - 1)
		mvwprintw(win, i, n * 3, "|");
	wrefresh(win);
	wattroff(win, COLOR_PAIR(11));
}

void		curse_color(t_vm *vm, t_scv *scv, int pc, int color)//colors mem depending on thread creator
{
	if (color == 14)
	{
		wattron(vm->curse.win, COLOR_PAIR(color));
		mvwprintw(vm->curse.win, 3 + pc / vm->curse.n, 1 + \
			(pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
		wattroff(vm->curse.win, COLOR_PAIR(color));
	}
	else
	{
		wattron(vm->curse.win, COLOR_PAIR(vm->creep[pc] + color));
		mvwprintw(vm->curse.win, 3 + pc / vm->curse.n, 1 + \
			(pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
		wattroff(vm->curse.win, COLOR_PAIR(vm->creep[pc] + color));
	}
	wrefresh(vm->curse.win);
	(void)scv;//
}

void        curse_scv(t_vm *vm)//disp info about working scvs right of mem
{
    t_scv   *scv_lst;
    int     i;
	int		reg;

    i = 0;
	scv_lst = vm->scv;
	while (scv_lst)
	{
		if (!(scv_lst->cooldown))
			curse_color(vm, scv_lst, scv_lst->pc, 2);
		else
			curse_color(vm, scv_lst, scv_lst->pc, 1);
		if (i < 12)
		{
			wattron(vm->curse.win, COLOR_PAIR(0 + (i << 1)));
			mvwprintw(vm->curse.win, 100 + i, 250, "Scv %d at vm->memory[%d] active in %03d", i, scv_lst->pc, scv_lst->cooldown);
			reg = 0;
			// while (reg < REG_NUMBER)
				// mvwprintw(vm->curse.win, 100 + i, 250, "REG[%d] %x\n", reg, scv_lst->reg[1]);
			wattroff(vm->curse.win, COLOR_PAIR(0 + (i << 1)));
			++i;
		}
		scv_lst = scv_lst->next;
	}
	wrefresh(vm->curse.win);
}


/*
** 46 00 00 00|	scv:			reg:45 45 00 00 45 45 00 00 45 45 00 00 45 45 00 00
** 00 00 00 00|		pc = 0			45 45 00 00 45 45 00 00 45 45 00 00 45 45 00 00
** 00 00 00 00|		carry = 0		45 45 00 00 45 45 00 00 45 45 00 00 45 45 00 00
** 00 00 00 00|		live = 0		45 45 00 00 45 45 00 00 45 45 00 00 45 45 00 00
*/


/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void    curse_memory(t_vm *vm)//disp memory
{
	size_t	pc;

	wattron(vm->curse.win, COLOR_PAIR(11));
	mvwprintw(vm->curse.win, 1, 2, "Current Cycle : %d", vm->cycle);
	mvwprintw(vm->curse.win, 1, 30, "Cycles to Die : %d", vm->cycle_to_die);
	mvwprintw(vm->curse.win, 1, 60, "Threads Alive : %d", vm->nb_scv);
	mvwprintw(vm->curse.win, 1, 90, "Game Speed : %02d [+] [-]", vm->curse.speed);
	wattroff(vm->curse.win, COLOR_PAIR(11));

	pc = 0;
	while (pc < MEM_SIZE)
	{
		wattron(vm->curse.win, COLOR_PAIR(vm->creep[pc]));
		mvwprintw(vm->curse.win, 3 + pc / vm->curse.n, 1 + (pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
		wattroff(vm->curse.win, COLOR_PAIR(vm->creep[pc]));
		++pc;
	}
	wrefresh(vm->curse.win);
	curse_scv(vm);
}


void		curse_init(t_vm *vm)
{
    int		i;

	vm->curse.speed = 2;
	vm->curse.pause = 1;
	initscr();
    getmaxyx(stdscr, vm->curse.y, vm->curse.x);
//	mvwprintw(vm->curse.win, 32, 220, "COLUMNS : %d", col);//
	vm->curse.n = vm->curse.x / 3;
	i = 1;
	while (i < vm->curse.n)
    	i <<= 1;
	if ((vm->curse.n = i >> 1) < 1)
		vm->curse.n = 4;
    start_color();
//	init_color(COLOR_CRIMSON, 0, 500, 1000); // use its own color instead
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_RED);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);
	init_pair(8, COLOR_CYAN, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_WHITE, COLOR_CYAN);
	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_GREEN);
	init_pair(13, COLOR_WHITE, COLOR_GREEN);
	init_pair(14, COLOR_YELLOW, COLOR_YELLOW);
//	vm->curse.pause = 1;
//	curse_players(vm);
	vm->curse.win = newwin(vm->curse.y, vm->curse.x, 0, 0);
	cbreak();
	nodelay(vm->curse.win, TRUE);
	noecho();
	curse_frame(vm->curse.win, vm->curse.y, vm->curse.x, vm->curse.n);
	curse_memory(vm);
//	box(vm->curse.win, '-' , '|');
//
//	vm->win = subwin(stdscr, row + 2, col + 2, 0, 0); // TTY  !!!!!!!!!!
//	box(vm->win, ACS_VLINE, ACS_HLINE);
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
