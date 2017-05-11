/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_glhf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/11 21:51:39 by agrumbac         ###   ########.fr       */
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

//	ft_putnbr(vm->rc[vm->memory[scv->pc]].dir_size);
//	ft_printf("==%d==\n", vm->memory[scv->pc]);
	if (type == REG_CODE)
	{
		arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)];
		if (arg < 1 || arg > REG_NUMBER)
			*pc = -1;
		// if (NEED DEREFENCING)// most ?
		// 	arg = mutate(vm, scv, arg, type);
	}
	else if (type == DIR_CODE)
		while (i++ < vm->rc[vm->redcode].dir_size)
			arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)] | (arg << 8);
	else if (type == IND_CODE)
	{
		while (i++ < IND_SIZE)
			arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)] | (arg << 8);
		arg &= (MEM_SIZE - 1);
		// if (NEED DEREFENCING)// all but 1 or 2..?
		// 	arg = mutate(vm, scv, arg, type);
	}
	return (arg);
}

/*
** check coding byte
** vm->type[i]  01 10 10 00
** vm->rc[redcode].arg[i] -> {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
** i is tab index;
*/

static int	check_octal(t_vm *vm, t_scv *scv)
{
	unsigned char	octal;
	int				n;
	int				pc;

	if ((octal = vm->memory[++scv->pc & (MEM_SIZE - 1)]) & 3)
		return (0);
	pc = 0;
	n = 0;//vm->rc[vm->redcode].arg_max;
	while (n < vm->rc[vm->redcode].arg_max)
	{
//		i = vm->rc[vm->redcode].arg_max - n;ft_printf("aābbbbbbbb");//
		vm->type[n] = (octal >> ((3 - n) << 1)) & 3; // 01 00 00 00
		if (!((vm->rc[vm->redcode].arg[n] >> (vm->type[n] - 1)) & 1))
			return (0);
		vm->arg[n] = get_args(vm, scv, &pc, vm->type[n]);
		if (pc < 0)
			return (0);
		//ft_printf("type %#08b\n", vm->type[n]);//
	//	ft_printf("vm->redcode %d\n", vm->rc[vm->redcode].arg[n]);//
		//ft_printf("arg %d\n", vm->arg[n]);//
		++n;
	}
	scv->pc = (scv->pc + pc) & (MEM_SIZE - 1);
	return (1);
}

static int	fill_args(t_vm *vm, t_scv *scv)
{
	int		i;
	int		n;
	int		pc;

	pc = 0;
	n = vm->rc[vm->redcode].arg_max;
	while (n)
	{
		i = vm->rc[vm->redcode].arg_max - n;
		vm->arg[i] = get_args(vm, scv, &pc, \
			vm->rc[vm->redcode].arg[i] - (vm->rc[vm->redcode].arg[i] >> 2));// 1=1 2=2 4=3 oh my dayum
		if (pc < 0)
			return (0);
		--n;
	}
	scv->pc = (scv->pc + pc) & (MEM_SIZE - 1);
	return (1);
}

static void	fetch(t_vm *vm, t_scv *scv)
{
	if (0 < vm->redcode && vm->redcode < 17)
	{
		if (!vm->rc[vm->redcode].octal)
			fill_args(vm, scv);
		else
			if (!(check_octal(vm, scv)))
				return ;
		vm->rc[vm->redcode].func(vm, scv);
		scv->cooldown = vm->rc[vm->redcode].cooldown;
	}
	else
		scv->pc = (scv->pc + 1) & (MEM_SIZE - 1);
}



// IMPORTANT!! TODO
// void		skip_if_octal_or_args_are_bullcrap()
// {
// 	if (octal)
// 	{
// 		pc+= sum(vm->types[])
// 	}
// 	else
// 	{
// 		pc+= sum(vm->rc.arg[])
// 	}
// }


/*
** go through our scvus list and :
** 1) check for redcode instructions redcode = vm->memory[lst->pc % MEM_SIZE];
** 2) execute the redcode : fetch(vm, lst, redcode);
** 3) check how long it will have to wait rc_cost(&lst->cooldown, redcode);
*/

static void	get_scv_redcode(t_vm *vm, t_scv **scv)
{
	t_scv		*lst;
	int			i;

	lst = *scv;
	while (lst)
	{
		i = 0;
	//	ft_printf("Hello Im scv %i at memory[%d]\n", vm->nb_scv - i++, lst->pc);//
		if (!(lst->cooldown))
		{
			vm->redcode = vm->memory[lst->pc & (MEM_SIZE - 1)];  // % n is same as & (n-1) !!!!!!!!!!!!!!!!
			fetch(vm, lst);
		}
		else
			--lst->cooldown;
		lst = lst->next;
	}
}

void		gl_hf(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	init_scv(vm);
	if (vm->flags & F_VISUAL)
		curse_init(vm);
	while (vm->scv)//vm->cycle < 1)// && vm->scv)
	{
//		if (!user_input(vm))
//			break ;
		if (vm->flags & F_VISUAL)
		{
			usleep(200000 - vm->curse.speed * 20000);
			while (!user_input(vm) || vm->curse.pause)
				;
		}
//		while (!user_input(vm) && vm->curse.pause)
//			;
//		nodelay(stdscr, vm->flags & F_PAUSE);
		get_scv_redcode(vm, &vm->scv);
//		sleep(vm->curse.speed);
		if (vm->cycle++ == vm->dump && vm->dump > -1)
			break;
		if (vm->cycle_to_die-- < 1)  // !!! does cycle 0 exist? !!!
		{
			reset_cycle(vm);
			kill_scv(vm, &vm->scv);
		}
	}
}
