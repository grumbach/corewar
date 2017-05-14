/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_glhf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/14 23:45:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Our main program
** gcc -framework GLUT -framework OpenGL -framework Cocoa opengl.gl -o vizualiser
*/

static int	user_input(t_vm *vm)
{
	int		key;

	key = wgetch(vm->curse.win);
	//	return (1);
//	mvprintw(200, 300, "key : %d", key);//(key);
	if (key == KEY_PLUS && vm->curse.speed < 10)
		++vm->curse.speed;
	else if (key == KEY_MINUS && vm->curse.speed > 0)
		--vm->curse.speed;
//	else if (key == KEY_SPACE)
//		while ((key = getch()) != KEY_SPACE) // MOCHE !!
//			;
	else if (key == KEY_SPACE)
		vm->curse.pause = 1 - vm->curse.pause;
	else if (key == KEY_ESCAPE)
	{
	//	kill_all_scv; // !!!!!!!!!!!!!!!!!! -> TO_DO
		delwin(vm->curse.win);
	//	clear();
	//	refresh();
		endwin();
		exit(0);
	}
//	ft_putnbr(vm->curse.pause);
	//	ft_putnbr(vm->curse.key);
	curse_memory(vm);
	return (key);
}

static unsigned int	get_args(t_vm *vm, t_scv *scv, int *pc, unsigned char type)
{
    unsigned int	arg;
	int				i;

	i = 0;
	arg = 0;
	if (type == REG_CODE)
	{
		arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)];
		if (arg < 1 || arg > REG_NUMBER)
			*pc = -1;
	}
	else if (type == DIR_CODE)
		while (i++ < vm->rc[vm->redcode].dir_size)
			arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)] | (arg << 8);
	else if (type == IND_CODE)
	{
		while (i++ < IND_SIZE)
			arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)] | (arg << 8);
		arg &= (MEM_SIZE - 1);
	}
	return (arg);
}

/*
** check coding byte
** vm->type[i]  01 10 10 00
** vm->rc[redcode].arg[i] -> {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
** i is tab index;
*/

static void	check_octal(t_vm *vm, t_scv *scv, int *pc)
{
	unsigned char	octal;
	int				arg;

	if ((octal = vm->memory[scv->pc + ++(*pc) & (MEM_SIZE - 1)]) & 3)
	{
		*pc = -1;
		return ;
	}
	arg = 0;
	while (arg < vm->rc[vm->redcode].arg_max)
	{
		vm->type[arg] = (octal >> ((3 - arg) << 1)) & 3; // 01 00 00 00
		if (!((vm->rc[vm->redcode].arg[arg] >> (vm->type[arg] - 1)) & 1))
		{
			*pc = -1;
			return ;
		}
		vm->arg[arg] = get_args(vm, scv, pc, vm->type[arg]);
		if (*pc < 0)
			return ;
		++arg;
	}
}

static void	fill_args(t_vm *vm, t_scv *scv, int *pc)
{
	int		i;
	int		arg;

	arg = vm->rc[vm->redcode].arg_max;
	while (arg)
	{
		i = vm->rc[vm->redcode].arg_max - arg;
		vm->arg[i] = get_args(vm, scv, pc, \
			vm->rc[vm->redcode].arg[i] - (vm->rc[vm->redcode].arg[i] >> 2));// 1=1 2=2 4=3 oh my dayum
		if (*pc < 0)
			return ;
		--arg;
	}
}

static void	fetch(t_vm *vm, t_scv *scv)
{
	int		pc;

	pc = 0;
	if (0 < vm->redcode && vm->redcode < 17)
	{
		if (!vm->rc[vm->redcode].octal)
			fill_args(vm, scv, &pc);
		else
			check_octal(vm, scv, &pc);
		if (pc >= 0)
		{
			vm->rc[vm->redcode].func(vm, scv);
			scv->cooldown = vm->rc[vm->redcode].cooldown;
			scv->pc = (scv->pc + pc) & (MEM_SIZE - 1);
		}
		else
		{
			scv->carry = 0;
			scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
		}
	}
	else
		scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}

/*
** go through our scvus list and :
** 1) check for redcode instructions redcode = vm->memory[lst->pc % MEM_SIZE];
** 2) execute the redcode : fetch(vm, lst, redcode);
** 3) check how long it will have to wait rc_cost(&lst->cooldown, redcode);
*/

static void	get_scv_redcode(t_vm *vm, t_scv **scv)
{
	t_scv		*lst;

	lst = *scv;
	while (lst)
	{
		if (!(lst->cooldown))
		{
			vm->redcode = vm->memory[lst->pc & (MEM_SIZE - 1)];
			fetch(vm, lst);
		}
		else
			--lst->cooldown;
		lst = lst->next;
	}
}

/*
** once vm->cycle_to_die reaches 0 it is reset
** to cycle_to_die original value - CYCLE_DELTA making next clear quicker
** we kill all scvus who didn't use live
*/

void	reset_cycle(t_vm *vm)
{
	static int	cycle_to_die = CYCLE_TO_DIE;

	if (++vm->checks == MAX_CHECKS || vm->nb_total_live >= NBR_LIVE)
	{
		vm->checks = 0;
		cycle_to_die -= CYCLE_DELTA;
	}
	vm->cycle_to_die = cycle_to_die;
	kill_dead_scvs(vm, &vm->scv);
}

void		gl_hf(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	init_scv(vm);
	if (vm->flags & F_VISUAL)
		curse_init(vm);
	while (vm->scv)//vm->cycle < 1)// && vm->scv)
	{
		if (vm->flags & F_VISUAL)
		{
			usleep(200000 - vm->curse.speed * 20000);
			while (!user_input(vm) || vm->curse.pause)
				;
		}
		get_scv_redcode(vm, &vm->scv);
		if (vm->cycle++ == vm->dump && vm->dump > -1)
			break;
		if (!vm->cycle_to_die--)
			reset_cycle(vm);
	}
}
