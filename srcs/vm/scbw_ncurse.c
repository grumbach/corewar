/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_ncurse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:16:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/11 05:55:09 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		curse_window(WINDOW *win, int y, int x)
{
	int		i;

	wattron(win, COLOR_PAIR(6));
	mvwprintw(win, 0, 0, "+");
	mvwprintw(win, y - 1, 0, "+");
	mvwprintw(win, 0, x - 1, "+");
	mvwprintw(win, y - 1, x - 1, "+");
	i = 0;
	while (++i < 67)
	{
		mvwprintw(win, i, 0, "|");
		mvwprintw(win, i, x - 1, "|");
	}
	i = 0;
	while (++i < 156)
	{
		mvwprintw(win, 0, i, "-");
		mvwprintw(win, y - 1, i, "-");
	}
	wrefresh(win);
	wattroff(win, COLOR_PAIR(6));
}

/*
** attron is used to put the green color with attron(COLOR_PAIR(2));
*/

void        curse_scv(t_vm *vm)//disp info about working scvs right of mem
{
    t_scv   *scv_lst;
    int     i;

    i = 0;
	scv_lst = vm->scv;
	while (scv_lst)
	{
		if (!(scv_lst->cooldown))
		{
			attron(COLOR_PAIR(10));
			mvwprintw(vm->curse.win, 3 + scv_lst->pc / vm->curse.n, 1 + (scv_lst->pc % vm->curse.n) * 3, "%02x", vm->memory[scv_lst->pc]);
			attroff(COLOR_PAIR(10));
			wrefresh(vm->curse.win);
		}
	//	mvwprintw(vm->curse.win, 3 + scv_lst->pc / vm->curse.n, 1 + (scv_lst->pc % vm->curse.n) * 3, "%02x", vm->memory[scv_lst->pc]);
		if (i < 6)
		{
			mvwprintw(vm->curse.win, 100 + i % 3, 100 + (i / 3) * 150, "Scv %d at vm->memory[%d] active in %03d", i, scv_lst->pc, scv_lst->cooldown);
			mvwprintw(vm->curse.win, 100 + i % 3, 100 + (i / 3) * 150, "REG[1] %d \tREG[2] %d \tREG[3] %d\n", scv_lst->reg[1], scv_lst->reg[2], scv_lst->reg[3]);
			++i;
		}
		scv_lst = scv_lst->next;
		attroff(COLOR_PAIR(1 + i));
	}
	wrefresh(vm->curse.win);
}

void		curse_color(t_vm *vm, t_scv *scv, int i)//colors mem depending on thread creator
{
	attron(COLOR_PAIR(3));
	mvwprintw(vm->curse.win, 3 + scv->pc / vm->curse.n, 1 + (scv->pc % vm->curse.n) * 3,
	"%02x", vm->memory[(scv->pc + (3 - i) % IDX_MOD) & (MEM_SIZE - 1)]);
	attroff(COLOR_PAIR(3));
	wrefresh(vm->curse.win);
}


/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void    curse_memory(t_vm *vm)//disp memory
{
	size_t	pc;

	curse_window(vm->curse.win, vm->curse.y, vm->curse.x);
	move(1, 10);
	attron(COLOR_PAIR(3)); // replace the value 2 by corresponding scv color
	mvwprintw(vm->curse.win, 1, 2, "Current Cycle : %d", vm->cycle);
	mvwprintw(vm->curse.win, 1, 30, "Remaining Cycles : %d", vm->cycle_to_die);
	mvwprintw(vm->curse.win, 1, 60, "Threads alive : %d", vm->nb_scv);
	mvwprintw(vm->curse.win, 1, 90, "Game Speed : %02d", vm->curse.speed);
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(6));
	pc = 0;
	while (pc < MEM_SIZE)
	{
		mvwprintw(vm->curse.win, 3 + pc / vm->curse.n, 1 + (pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
		++pc;
	}
	attroff(COLOR_PAIR(6));
	wrefresh(vm->curse.win);
	curse_scv(vm);
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
*/

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
    init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_WHITE);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);
//	vm->curse.pause = 1;
//	curse_players(vm);
	vm->curse.win = newwin(200, 150, 0, 0);
	cbreak();
	nodelay(vm->curse.win, TRUE);
	noecho();
//	box(vm->curse.win, '-' , '|');	
//	
//	vm->win = subwin(stdscr, row + 2, col + 2, 0, 0); // TTY  !!!!!!!!!!
//	box(vm->win, ACS_VLINE, ACS_HLINE);
}


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
