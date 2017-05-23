/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scbw_redcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 23:29:09 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/23 19:58:02 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static uint	get_args(t_vm *vm, t_scv *scv, int *pc, unsigned char type)
{
	uint	arg;
	int		i;

	i = 0;
	arg = 0;
	if (type == REG_CODE)
	{
		arg = vm->memory[(scv->pc + ++(*pc)) % MEM_SIZE];
		if (arg < 1 || arg > REG_NUMBER)
			*pc |= 0x10;
	}
	else if (type == DIR_CODE)
		while (i++ < vm->rc[scv->redcode].dir_size)
			arg = vm->memory[(scv->pc + ++(*pc)) % MEM_SIZE] | (arg << 8);
	else if (type == IND_CODE)
		while (i++ < IND_SIZE)
			arg = vm->memory[(scv->pc + ++(*pc)) % MEM_SIZE] | (arg << 8);
	return (arg);
}

static void	fill_args(t_vm *vm, t_scv *scv, int *pc)
{
	int		i;
	int		arg;

	arg = vm->rc[scv->redcode].arg_max;
	while (arg)
	{
		i = vm->rc[scv->redcode].arg_max - arg;
		vm->arg[i] = get_args(vm, scv, pc, \
			vm->rc[scv->redcode].arg[i] - (vm->rc[scv->redcode].arg[i] >> 2));
		if (*pc > 0x10)
			return ;
		--arg;
	}
}

/*
** check coding byte
** vm->type[i]  01 10 10 00
** vm->rc[redcode].arg[i] -> {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
** i is tab index;
*/

static void	check_ocp(t_vm *vm, t_scv *scv, int *pc)
{
	unsigned char	ocp;
	int				arg;

	if ((ocp = vm->memory[scv->pc + ++(*pc) % MEM_SIZE]) & 3)
	{
		*pc |= 0x10;
		return ;
	}
	arg = 0;
	while (arg < vm->rc[scv->redcode].arg_max)
	{
		vm->type[arg] = (ocp >> ((3 - arg) << 1)) & 3;
		if (!((vm->rc[scv->redcode].arg[arg] >> (vm->type[arg] - 1)) & 1))
		{
			*pc |= 0x10;
			return ;
		}
		vm->arg[arg] = get_args(vm, scv, pc, vm->type[arg]);
		if (*pc > 0x10)
			return ;
		++arg;
	}
}

static void	fetch(t_vm *vm, t_scv *scv)
{
	int		pc;

	if (vm->flags & F_VISUAL)
		curse_color(vm, scv->pc, scv->color + 2);
	pc = 0;
	if (vm->rc[scv->redcode].ocp)
		check_ocp(vm, scv, &pc);
	else
		fill_args(vm, scv, &pc);
	if (pc < 0x10)
		vm->rc[scv->redcode].func(vm, scv);
	scv->pc = (scv->pc + (pc & 0xf) + 1) % MEM_SIZE;
	scv->redcode = 0;
}

/*
** go through our scvus list and :
** 1) check for redcode instructions redcode = vm->memory[lst->pc % MEM_SIZE];
** 2) execute the redcode : fetch(vm, lst, redcode);
** 3) check how long it will have to wait rc_cost(&lst->cooldown, redcode);
*/

void		get_scv_redcode(t_vm *vm)
{
	t_scv		*scv;

	scv = vm->scv;
	while (scv)
	{
		if (!scv->redcode)
		{
			scv->redcode = vm->memory[scv->pc % MEM_SIZE];
			if (0 < scv->redcode && scv->redcode < 17)
				scv->cooldown = vm->rc[scv->redcode].cooldown - 1;
			else if (!(scv->redcode = 0))
				++scv->pc;
		}
		if (!(scv->cooldown) && scv->redcode)
			fetch(vm, scv);
		else
		{
			--scv->cooldown;
			if (vm->flags & F_VISUAL)
				curse_color(vm, scv->pc, scv->color + 3 \
					- (vm->memory[scv->pc % MEM_SIZE] == 1 ? 1 : 0));
		}
		scv = scv->next;
	}
}
