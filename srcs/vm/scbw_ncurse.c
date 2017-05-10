/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_ncurse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:16:13 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/10 23:55:20 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	curse_display_cycles(t_vm *vm)
{
	move(1, 10);
	attron(COLOR_PAIR(3)); // replace the value 2 by corresponding scv color
	printw("Current Cycle : %d", vm->cycle);
	printw("\t\tRemaining Cycles : %d", vm->cycle_to_die);
	printw("\t\tThreads alive : %d", vm->nb_scv);
	attroff(COLOR_PAIR(3));
}

/*
** attron is used to put the green color with attron(COLOR_PAIR(2));
*/

void        curse_display_threads(t_vm *vm)
{
    t_scv   *scv_lst;
    int     i;

    i = 0;
	scv_lst = vm->scv;
	while (scv_lst)
	{
		attron(COLOR_PAIR(1 + i)); // replace the value 2 by corresponding scv color
		if (vm->curse.n)
			mvprintw(3 + scv_lst->pc / vm->curse.n, 1 + (scv_lst->pc % vm->curse.n) * 3, "%02x", vm->memory[scv_lst->pc]);
		if (i < 6)
		{
			mvprintw(100 + i % 3, 100 + (i / 3) * 150, "Scv %d at vm->memory[%d] active in %03d", i, scv_lst->pc, scv_lst->cooldown);
			mvprintw(100 + i % 3, 100 + (i / 3) * 150, "REG[1] %d \tREG[2] %d \tREG[3] %d\n", scv_lst->reg[1], scv_lst->reg[2], scv_lst->reg[3]);
		}
		scv_lst = scv_lst->next;
		attroff(COLOR_PAIR(1 + i));
        ++i;
	}

	refresh();
}

void		curse_color(t_vm *vm, t_scv *scv, int i)//colors memory depending on thread creator
{
	attron(COLOR_PAIR(3));
	mvprintw(3 + scv->pc / vm->curse.n, 1 + (scv->pc % vm->curse.n) * 3,
	"%02x", vm->memory[(scv->pc + (3 - i) % IDX_MOD) & (MEM_SIZE - 1)]);
	attroff(COLOR_PAIR(3));
}


/*
** at the end of nbr_cycles executed, dump the memory on the standard output
** and quit the game. The memory must be dumped in the hexadecimal format with
** 32 octets per line.
*/

void    curse_display_memory(t_vm *vm, int n)
{
	size_t	pc;

	if (n == 32)
	{
		mvprintw(68, 10, "Reached %d Cycle, Dumping Memory", vm->dump);
		n = 32;
	}
	else
		n = vm->curse.n;
	pc = 0;
	attron(COLOR_PAIR(6));
	while (pc < MEM_SIZE)
	{
		mvprintw(3 + pc / vm->curse.n, 1 + (pc % vm->curse.n) * 3, "%02x", vm->memory[pc]);
		++pc;
	}
	attroff(COLOR_PAIR(3));
	refresh();
}

/*
** display player info
*/

static void	curse_players(t_vm *vm)//
{
	int	i;
	int	offset;

	i = 0;
	offset = 240;
	mvprintw(20, offset, "Our Gladiators, Ave Caesar, Morituri te salutant :");
	while (i < vm->nb_players)
	{
		mvprintw(22 + i * 5, offset, "\tPlayer %d : %s", vm->core[i].id, vm->core[i].prog_name);
		mvprintw(23 + i * 5, offset, "\tComment : %s", vm->core[i].comment);
		mvprintw(24 + i * 5, offset, "\tWeight : %X", vm->core[i].prog_size);
		++i;
	}
}

void		curse(t_vm *vm)
{
    curse_display_cycles(vm);
    curse_display_memory(vm, 64);
    curse_display_threads(vm);

//	mvwprintw(vm->win, 1200, 300, "%sHello World\n", "\033[35m", 123);
//	mvprintw(0, 0, "Hello, world!");
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
*/

void		init_curse(t_vm *vm)
{
    int		i;
	int     row;
    int     col;

	initscr();
    getmaxyx(stdscr, row, col);
//	mvprintw(32, 220, "COLUMNS : %d", col);//
	vm->curse.n = col / 3;
	i = 1;
	while (i < vm->curse.n)
    	i <<= 1;
	vm->curse.n = i >> 1;
    start_color();
//	init_color(COLOR_CRIMSON, 0, 500, 1000); // use its own color instead
    init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	noecho();
	curse_players(vm);
//	vm->win = subwin(stdscr, row + 2, col + 2, 0, 0); // TTY  !!!!!!!!!!
//	box(vm->win, ACS_VLINE, ACS_HLINE);
}