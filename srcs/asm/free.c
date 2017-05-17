/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 18:01:51 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:25:49 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void	free_label_arg(t_env *env)
{
	t_arg		*tmp_a;
	t_label		*tmp_l;

	while (env->inst->label)
	{
		ft_memdel((void **)&env->inst->label->name);
		tmp_l = env->inst->label;
		env->inst->label = env->inst->label->next;
		ft_memdel((void **)&tmp_l);
	}
	while (env->inst->arg)
	{
		ft_memdel((void **)&env->inst->arg->name);
		ft_memdel((void **)&env->inst->arg->label);
		tmp_a = env->inst->arg;
		env->inst->arg = env->inst->arg->next;
		ft_memdel((void **)&tmp_a);
	}
}

void		free_env(t_env *env)
{
	t_inst		*tmp_i;

	while (env->inst)
	{
		ft_memdel((void **)&env->inst->instruction);
		free_label_arg(env);
		tmp_i = env->inst;
		env->inst = env->inst->next;
		ft_memdel((void **)&tmp_i);
	}
	ft_memdel((void **)&env->name);
	ft_memdel((void **)&env->name_file);
	ft_memdel((void **)&env->comment);
	ft_memdel((void **)&env->header);
	ft_memdel((void **)&env->inst);
	ft_memdel((void **)&env);
}
