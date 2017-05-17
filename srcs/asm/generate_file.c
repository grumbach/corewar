/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 23:36:19 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:42:20 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void			check_last_inst(t_env *env, int part)
{
	t_inst		*inst;

	inst = env->inst;
	if (!inst)
		asm_error(22, env, 0);
	if (part == 1)
	{
		while (inst && inst->next)
			inst = inst->next;
	}
	if (part == 2)
	{
		while (inst && inst->next)
			inst = inst->next;
		if (inst && !inst->instruction)
			inst->pos = env->header->prog_size;
	}
}

static void			write_header(int fd, t_env *env)
{
	env->header->magic = ft_endian_4_bytes(env->header->magic);
	env->header->prog_size = ft_endian_4_bytes(env->header->prog_size);
	write(fd, env->header, sizeof(t_header));
}

static void			write_cor(t_env *env)
{
	int				fd;
	t_inst			*inst;

	inst = env->inst;
	fd = open(env->name_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	fd == -1 ? asm_error(13, env, 0) : 0;
	write_header(fd, env);
	write_instruction(fd, env);
}

static void			print_success(t_env *env)
{
	int		i;
	int		slash;

	i = 0;
	slash = 0;
	while (env->name_file[i])
	{
		if (env->name_file[i] == '/')
			slash = i;
		i++;
	}
	if (slash)
		env->name_file = ft_strsub_f(env->name_file, slash + 1,
			ft_strlen(env->name_file) - slash);
	ft_printf("Writing output program to %s\n", env->name_file);
}

void				generate_file(t_env *env)
{
	check_last_inst(env, 1);
	generate_header(env);
	check_last_inst(env, 2);
	check_if_label_exist(env);
	env->name_file = ft_strjoin_f1(env->name_file, ".cor");
	write_cor(env);
	print_success(env);
	free_env(env);
}
