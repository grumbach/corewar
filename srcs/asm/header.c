/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:22:51 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:00:35 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void			generate_header(t_env *env)
{
	int			i;
	t_inst		*inst;

	i = 0;
	env->header = (t_header *)ft_memalloc(sizeof(t_header));
	!(env->header) ? malloc_error(0, env) : 0;
	inst = env->inst;
	env->header->magic = COREWAR_EXEC_MAGIC;
	env->header->prog_size = 0;
	while (env->name[i])
	{
		env->header->prog_name[i] = env->name[i];
		i++;
	}
	while (inst)
	{
		env->header->prog_size += inst->size;
		inst = inst->next;
	}
	i = 0;
	while (env->comment[i])
	{
		env->header->comment[i] = env->comment[i];
		i++;
	}
}
