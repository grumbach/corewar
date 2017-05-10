/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_glhf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 01:11:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/10 21:59:41 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** Our main program
** gcc -framework GLUT -framework OpenGL -framework Cocoa opengl.gl -o vizualiser
*/

void		gl_hf(t_vm *vm)
{
	int		user_input;

	vm->cycle_to_die = CYCLE_TO_DIE;
	init_scv(vm);
	if (vm->flags >> 1)
	{
		curse(vm);
		sleep(1);
	}
	user_input = getch();
	while (vm->scv)//vm->cycle < 1)// && vm->scv)
	{
	//		vm->win->erase();
		if (vm->flags >> 1)
			curse(vm);

		if (vm->cycle++ == vm->dump && vm->dump > -1)
		{
			curse_display_memory(vm, 32);
			break;
		}
		get_scv_redcode(vm, &vm->scv);
		//	mvprintw(50, 200, "YAAAAAaaaaaaa4");////////////
		if (vm->cycle_to_die-- < 1)  // !!! does cycle 0 exist? !!!
		{
			reset_cycle(vm);
			kill_scv(vm, &vm->scv);
		}
		refresh();
		user_input = getch();
		if (user_input == 126 && vm->curse.speed > 0)
			--vm->curse.speed;
		else if (user_input == 125 && vm->curse.speed < 10)
			++vm->curse.speed;
		sleep(vm->curse.speed);
	}
}


static unsigned int	get_args(t_vm *vm, t_scv *scv, int *pc, unsigned char type)
{
    unsigned int	arg;
	int				i;

	i = 0;
	arg = 0;

//	ft_putnbr(vm->rc[vm->memory[scv->pc]].dir_size);
	if (type == REG_CODE)
	{
		arg = vm->memory[(scv->pc + ++(*pc)) & (MEM_SIZE - 1)];
		if (arg < 1 || arg > REG_NUMBER)
			*pc = -1;
	}
	else if (type == DIR_CODE)
		while (i++ < vm->rc[vm->memory[scv->pc]].dir_size)
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

static int	check_octal(t_vm *vm, t_scv *scv, int redcode)
{
	unsigned char	octal;
//	int				i;
	int				n;
	int				pc;


	//	mvprintw(55, 200, "Octal : %d", octal);//
	if ((octal = vm->memory[++scv->pc & (MEM_SIZE - 1)]) & 3)
		return (0);
	pc = 0;
	n = 0;//vm->rc[redcode].arg_max;
	while (n < vm->rc[redcode].arg_max)
	{
//		i = vm->rc[redcode].arg_max - n;ft_printf("aābbbbbbbb");//
		vm->type[n] = (octal >> ((3 - n) << 1)) & 3; // 01 00 00 00
		if (!((vm->rc[redcode].arg[n] >> (vm->type[n] - 1)) & 1))
			return (0);
		vm->arg[n] = get_args(vm, scv, &pc, vm->type[n]);
		if (pc < 0)
			return (0);
		//ft_printf("type %#08b\n", vm->type[n]);//
	//	ft_printf("redcode %d\n", vm->rc[redcode].arg[n]);//
		//ft_printf("arg %d\n", vm->arg[n]);//
		++n;
	}
	scv->pc = (scv->pc + pc) & (MEM_SIZE - 1);
	return (1);
}

static int	fill_args(t_vm *vm, t_scv *scv, int redcode)
{
	int		i;
	int		n;
	int		pc;

	pc = 0;
	n = vm->rc[redcode].arg_max;
	while (n)
	{
		i = vm->rc[redcode].arg_max - n;
		vm->arg[i] = get_args(vm, scv, &pc, \
			vm->rc[redcode].arg[i] - (vm->rc[redcode].arg[i] >> 2));// 1=1 2=2 4=3 oh my dayum
		if (pc < 0)
			return (0);
		--n;
	}
	scv->pc = (scv->pc + pc) & (MEM_SIZE - 1);
	return (1);
}

void	fetch(t_vm *vm, t_scv *scv, int redcode)
{
	if (0 < redcode && redcode < 17)
	{
		if (!vm->rc[redcode].octal)
			fill_args(vm, scv, redcode);
		else
			if (!(check_octal(vm, scv, redcode)))
				return ;
		vm->rc[redcode].func(vm, scv);
		scv->cooldown = vm->rc[redcode].cooldown;
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

void		get_scv_redcode(t_vm *vm, t_scv **scv)
{
	t_scv		*lst;
	int			redcode;
	int			i;

	lst = *scv;
	while (lst)
	{
		i = 0;
	//	ft_printf("Hello Im scv %i at memory[%d]\n", vm->nb_scv - i++, lst->pc);//
		if (!(lst->cooldown))
		{
			redcode = vm->memory[lst->pc & (MEM_SIZE - 1)];  // % n is same as & (n-1) !!!!!!!!!!!!!!!!
			if (vm->flags & F_DISPLAY_SCV)
				mvprintw(30 + i++, 220, "Redcode: %d at memory[%d][%d]", redcode, lst->pc / vm->curse.n, lst->pc % vm->curse.n);//
			fetch(vm, lst, redcode);
		}
		else
			--lst->cooldown;
		lst = lst->next;
	}
}

/*
int		check_octal(t_vm *vm, t_scv *scv, int redcode, unsigned char octal)
{
	int		i;
	int		n;

	if (octal & 3)
		return (0);
	n = vm->rc[redcode].arg_max;
	while (n)
	{
		i = vm->rc[redcode].arg_max - n;
		vm->type[i] = (octal >> (n << 1)) & 3;
		if (!((vm->rc[redcode].arg[i] >> (vm->type[i] - 1)) & 1))
			return (0);
		--n;
	}
	return (1);
}*/
