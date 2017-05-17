/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:33:17 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:39:54 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int		check_if_label(char *line)
{
	int		i;
	char	*lchars;

	i = 0;
	lchars = ft_strdup(LABEL_CHARS);
	while (line[i])
	{
		if (line[i] == LABEL_CHAR && i > 0)
		{
			ft_memdel((void **)&lchars);
			return (1);
		}
		else if (!(ft_strchr(lchars, line[i])))
		{
			ft_memdel((void **)&lchars);
			return (0);
		}
		else
			i++;
	}
	ft_memdel((void **)&lchars);
	return (0);
}

int				get_opcode(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != '\t' && line[i] != ' ' &&
			line[i] != DIRECT_CHAR && line[i] != LABEL_CHAR)
		i++;
	tmp = ft_strsub(line, 0, i);
	i = 0;
	while (i <= 15)
	{
		if (!(ft_strcmp(tmp, g_op_tab[i].inst)))
		{
			ft_memdel((void **)&tmp);
			return ((i + 1) * 10);
		}
		i++;
	}
	ft_memdel((void **)&tmp);
	return (-1);
}

t_op			*get_optab(char *name)
{
	int		i;

	i = 0;
	while (g_op_tab[i].inst)
	{
		if (!(ft_strcmp(g_op_tab[i].inst, name)))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

int				get_type_line(char *l)
{
	char	*line;
	int		ret;

	line = ft_strtrim(l);
	if (!line[0])
		ret = 0;
	else if (line[0] == ';')
		ret = 1;
	else if (line[0] == COMMENT_CHAR)
		ret = 2;
	else if ((!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
		ret = 3;
	else if (!(ft_strncmp(line, COMMENT_CMD_STRING,
										ft_strlen(COMMENT_CMD_STRING))))
		ret = 4;
	else if (check_if_label(line))
		ret = 5;
	else
		ret = get_opcode(line);
	ft_memdel((void **)&line);
	return (ret);
}
