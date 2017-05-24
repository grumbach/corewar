/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 14:04:52 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/24 07:44:12 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** reverse 4 bytes 11000110 00011111 00111111 11111100
*/

unsigned int	ft_endian_4_bytes(unsigned int n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) |
					((n & 0xff) << 24));
}

int				get_ocp(char *inst, t_arg *arg)
{
	t_op	*op;
	char	*ret;
	t_arg	*tmp;
	int		i;

	tmp = arg;
	op = get_optab(inst);
	if (op && op->need_oc == 0)
		return (-1);
	ret = ft_strdup("");
	while (tmp)
	{
		if (tmp->name[0] == 'r')
			ret = ft_strjoin_f1(ret, "01");
		else if (tmp->name[0] == DIRECT_CHAR)
			ret = ft_strjoin_f1(ret, "10");
		else
			ret = ft_strjoin_f1(ret, "11");
		tmp = tmp->next;
	}
	while (ft_strlen(ret) != 8)
		ret = ft_strjoin_f1(ret, "00");
	i = ft_atoi_base(ret, 2);
	ft_memdel((void **)&ret);
	return (i);
}

int				contain_quote(char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void			cut_comment(char **line)
{
	int		i;
	int		todo;
	int		quote;

	quote = -1;
	i = 0;
	todo = 0;
	while (line[0][i])
	{
		line[0][i] == '"' ? quote *= -1 : 0;
		if (quote < 0 && (line[0][i] == COMMENT_CHAR || line[0][i] == ';'))
		{
			todo++;
			break ;
		}
		i++;
	}
	if (todo && i >= 1)
	{
		line[0] = ft_strsub_f(line[0], 0, i);
		line[0] = ft_strtrim_f(line[0]);
	}
}

void			check_after_quote(char *tmp, t_env *env, int e, int j)
{
	while (tmp[j])
	{
		if (tmp[j] && tmp[j] == COMMENT_CHAR)
			break ;
		else if (tmp[j] && tmp[j] != ' ' && tmp[j] != '\t')
			asm_error(e, env, 0);
		j++;
	}
	ft_memdel((void **)&tmp);
}
