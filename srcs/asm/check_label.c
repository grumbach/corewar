/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 23:53:04 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/13 08:10:03 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int		find_label(char *label, t_env *env)
{
	t_inst		*inst;
	t_label		*slabel;

	inst = env->inst;
	while (inst)
	{
		slabel = inst->label;
		while (slabel)
		{
			if (!(ft_strcmp(label, slabel->name)))
				return (1);
			slabel = slabel->next;
		}
		inst = inst->next;
	}
	return (0);
}

void			check_if_label_exist(t_env *env)
{
	t_inst		*inst;
	t_arg		*arg;

	inst = env->inst;
	while (inst)
	{
		arg = inst->arg;
		while (arg)
		{
			if (arg->is_label)
				find_label(arg->label, env) ? 0 : asm_error(12, env, arg->line);
			arg = arg->next;
		}
		inst = inst->next;
	}
}
