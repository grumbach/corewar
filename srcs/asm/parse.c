/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 18:43:52 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:40:53 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void		put_file_name(char *file, t_env *env)
{
	char		*ext;
	char		*tmp_name;

	tmp_name = ft_strsub(file, 0, ft_strlen(file) - 2);
	ext = ft_strsub(file, ft_strlen(file) - 2, ft_strlen(file) - 1);
	if (ft_strcmp(ext, ".s") == 0)
		env->name_file = ft_strdup_f(tmp_name);
	else
	{
		ft_memdel((void **)&ext);
		ft_memdel((void **)&tmp_name);
		asm_error(1, env, 0);
	}
	ft_memdel((void **)&ext);
}

static void		init(t_env *env)
{
	env->name = NULL;
	env->name_file = NULL;
	env->comment = NULL;
	env->header = NULL;
	env->inst = NULL;
	env->nb_l = 0;
	env->fd = -1;
	env->have_label = 0;
	env->have_name = 0;
	env->have_comment = 0;
}

static int		check_line(char *l, t_env *env, int type)
{
	int		i;

	i = 0;
	if (type == 3 && env->have_name == 1)
		return (0);
	if (type == 4 && env->have_comment == 1)
		return (0);
	if ((type == 5 || type >= 10) && (env->have_name == 0 ||
				env->have_comment == 0))
		return (0);
	while (l[i + 1])
		i++;
	if (l[i] == ',')
		return (0);
	return (1);
}

static void		check_fd_file(t_env *env)
{
	char	c;

	if (env->fd && read(env->fd, &c, 1) <= 0)
		asm_error(21, env, -1);
	lseek(env->fd, 0, SEEK_SET);
}

t_env			*parse_s_file(char *file)
{
	t_env	*env;
	char	*line;
	int		line_type;
	int		gnl;

	env = (t_env *)ft_memalloc(sizeof(t_env));
	!(env) ? malloc_error(0, NULL) : 0;
	init(env);
	put_file_name(file, env);
	env->fd = open(file, O_RDONLY);
	check_fd_file(env);
	while ((gnl = get_next_line(env->fd, &line)) > 0)
	{
		env->nb_l++;
		line_type = get_type_line(line);
		cut_comment(&line);
		line_type = check_line(line, env, line_type) ? line_type : -1;
		line_type == 3 ? put_name(line, env) : 0;
		line_type == 4 ? put_comment(line, env) : 0;
		line_type == 5 ? put_label(line, env) : 0;
		line_type >= -1 && line_type <= 5 ? 0 : put_inst(line, env);
		free(line);
		line_type == -1 ? asm_error(10, env, 0) : 0;
	}
	return (env);
}
