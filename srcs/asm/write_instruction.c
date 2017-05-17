/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 13:23:00 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:38:54 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int				find_label_pos(char *search, t_env *env, t_arg *arg)
{
	t_inst	*inst;
	t_label	*lab;

	inst = env->inst;
	while (inst)
	{
		lab = inst->label;
		while (lab)
		{
			if (!(ft_strcmp(search, lab->name)))
				return (inst->pos);
			lab = lab->next;
		}
		inst = inst->next;
	}
	asm_error(12, env, arg->line);
	return (42);
}

void			write_instruction(int fd, t_env *env)
{
	t_inst		*inst;
	t_op		*op;

	inst = env->inst;
	while (inst)
	{
		if (inst->instruction)
		{
			op = get_optab(inst->instruction);
			write(fd, &(op->opcode), 1);
			if (inst->ocp != -1)
				write(fd, &(inst->ocp), 1);
			if (inst->arg)
				write_arg(fd, inst->arg, env, inst);
		}
		inst = inst->next;
	}
}
