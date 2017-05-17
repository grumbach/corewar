/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 23:27:26 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:38:42 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void			putrevcpy(int fd, char *src, int size)
{
	while (size--)
		write(fd, src + size, 1);
}

static void			write_r(int fd, char *r)
{
	int			i;
	char		c;

	i = 0;
	while (!(ft_isdigit(r[i])))
		i++;
	c = (char)ft_atoi(r + i);
	write(fd, &c, 1);
}

static void			write_dir(int fd, t_arg *arg, t_env *env, t_inst *inst)
{
	int		ret;

	if (arg->is_label)
	{
		ret = find_label_pos(arg->label, env, arg) - inst->pos;
		putrevcpy(fd, (char *)&ret, arg->size);
	}
	else
	{
		ret = ft_atoi(arg->name + 1);
		putrevcpy(fd, (char *)&ret, arg->size);
	}
}

static void			write_ind(int fd, t_arg *arg, t_env *env, t_inst *inst)
{
	int	ret;

	if (arg->is_label)
	{
		ret = find_label_pos(arg->label, env, arg) - inst->pos;
		putrevcpy(fd, (char *)&ret, 2);
	}
	else
	{
		ret = ft_atoi(arg->name);
		putrevcpy(fd, (char *)&ret, 2);
	}
}

void				write_arg(int fd, t_arg *arg, t_env *env, t_inst *inst)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp)
	{
		if (tmp->t == 1)
			write_r(fd, tmp->name);
		else if (tmp->t == 2)
			write_dir(fd, tmp, env, inst);
		else if (tmp->t == 4)
			write_ind(fd, tmp, env, inst);
		tmp = tmp->next;
	}
}
