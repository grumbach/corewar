/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 14:20:36 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 15:38:20 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void		last_join(char *s, t_env *env)
{
	int		i;
	char	*tojoin;

	i = 0;
	while (s[i] && s[i] != '"')
		i++;
	tojoin = ft_strsub(s, 0, i);
	env->name = ft_strjoin_f1(env->name, "\n");
	env->name = ft_strjoin_f1(env->name, tojoin);
	i++;
	while (s[i])
	{
		if (s[i] && s[i] == COMMENT_CHAR)
			break ;
		else if (s[i] && s[i] != ' ' && s[i] != '\t')
			asm_error(14, env, 0);
		i++;
	}
	free(s);
	ft_memdel((void **)&tojoin);
}

static void		name_process(t_env *env, char *tmp)
{
	char	c;
	char	*line;

	line = NULL;
	c = 0;
	ft_memdel((void **)&tmp);
	while (get_next_line(env->fd, &line) > 0)
	{
		env->nb_l++;
		if (contain_quote(line))
		{
			c++;
			last_join(line, env);
			break ;
		}
		else
		{
			env->name = ft_strjoin_f1(env->name, "\n");
			env->name = ft_strjoin_f1(env->name, line);
		}
		free(line);
	}
	if (!c)
		asm_error(4, env, 0);
}

static void		get_name(char *name, t_env *env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = ft_strsub(name, ft_strlen(NAME_CMD_STRING), \
			ft_strlen(name) - ft_strlen(NAME_CMD_STRING));
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	if (tmp[i] && tmp[i] == '"')
		i++;
	else
	{
		ft_memdel((void **)&tmp);
		asm_error(2, env, 0);
	}
	j = i;
	while (tmp[j] && tmp[j] != '"')
		j++;
	env->name = ft_strsub(tmp, i, j - i);
	if (!tmp[j])
		name_process(env, tmp);
	else
		ft_memdel((void **)&tmp);
}

void			put_name(char *l, t_env *env)
{
	int		i;
	char	*trim;

	i = 0;
	while (l[i] && (l[i] == ' ' || l[i] == '\t'))
		i++;
	trim = ft_strsub(l, i, ft_strlen(l) - i);
	if (!(ft_strncmp(trim, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
		get_name(trim, env);
	if (ft_strlen(env->name) > PROG_NAME_LENGTH)
	{
		ft_memdel((void **)&trim);
		asm_error(6, env, 0);
	}
	ft_memdel((void **)&trim);
	env->have_name = 1;
}
