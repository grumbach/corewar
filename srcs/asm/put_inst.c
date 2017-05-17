/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_inst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 22:40:39 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:03:24 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int			get_position(t_env *env)
{
	int		pos;
	t_inst	*tmp;

	pos = 0;
	tmp = env->inst;
	while (tmp->next)
	{
		pos += tmp->size;
		tmp = tmp->next;
	}
	return (pos);
}

static t_inst		*get_last_inst(t_env *env)
{
	t_inst	*tmp;

	tmp = NULL;
	if (!env->inst)
	{
		env->inst = (t_inst *)ft_memalloc(sizeof(t_inst));
		!env->inst ? malloc_error(0, env) : 0;
		env->inst->label = NULL;
		env->inst->instruction = NULL;
		env->inst->arg = NULL;
		env->inst->size = 0;
		env->inst->pos = 0;
		env->inst->ocp = -1;
		env->inst->next = NULL;
		return (env->inst);
	}
	tmp = env->inst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static char			*get_inst_name(char **l)
{
	int		i;
	char	*tmp;

	i = 0;
	while (l[0][i] && ft_isalpha(l[0][i]) && l[0][i] != DIRECT_CHAR)
		i++;
	tmp = ft_strsub(l[0], 0, i);
	l[0] = ft_strsub_f(l[0], i, ft_strlen(l[0]) - 1);
	l[0] = ft_strtrim_f(l[0]);
	return (tmp);
}

static int			get_inst_size(t_inst *inst, t_env *env)
{
	int		i;
	t_op	*op;
	int		ret;
	t_arg	*arg;

	i = 0;
	ret = 1;
	if (inst->arg == NULL)
		return (0);
	arg = inst->arg;
	op = get_optab(inst->instruction);
	ret += op->need_oc;
	while (arg)
	{
		ret += arg->size;
		arg = arg->next;
		i++;
	}
	if (i != op->nb_arg)
		asm_error(8, env, 0);
	return (ret);
}

void				put_inst(char *l, t_env *env)
{
	char		*trim;
	t_inst		*inst;

	trim = ft_strtrim(l);
	inst = get_last_inst(env);
	if (!env->have_label)
	{
		inst->next = (t_inst *)ft_memalloc(sizeof(t_inst));
		!inst->next ? malloc_error(0, env) : 0;
		inst = inst->next;
		inst->instruction = NULL;
		inst->arg = NULL;
	}
	inst->instruction = get_inst_name(&trim);
	get_arg(trim, inst, env);
	inst->size = get_inst_size(inst, env);
	inst->ocp = get_ocp(inst->instruction, inst->arg);
	inst->pos = get_position(env);
	inst->next = NULL;
	env->have_label = 0;
	ft_memdel((void **)&trim);
}
