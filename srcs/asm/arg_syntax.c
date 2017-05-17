/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 07:45:28 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/17 01:32:34 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void				process_valid_arg(char *arg, int *i, int dig, t_env *e)
{
	int check;

	check = 0;
	if (dig == 1)
	{
		if (arg[*i] == '-')
			(*i)++;
		while (arg[*i] && ft_isdigit(arg[*i]))
			(*i)++;
	}
	else if (!dig)
	{
		while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
			(*i)++;
	}
	else
	{
		while (arg[*i] && ft_isdigit(arg[*i]))
			(*i)++;
		check = ft_atoi(arg + 1);
		if (check < 0 || check > REG_NUMBER)
			asm_error(20, e, 0);
	}
}

void					arg_syntax_is_valid(char *arg, t_env *env)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n'
			&& arg[i] != '\v' && arg[i] != '\r' && arg[i] != '\f')
		i++;
	arg[i] ? asm_error(9, env, 0) : 0;
	i = 1;
	if (arg[0] && arg[0] == 'r')
		process_valid_arg(arg, &i, 3, env);
	else if (arg[0] && arg[0] == DIRECT_CHAR)
	{
		if (arg[1] && arg[1] == LABEL_CHAR)
		{
			i++;
			process_valid_arg(arg, &i, 0, env);
		}
		else
			process_valid_arg(arg, &i, 1, env);
	}
	else if (arg[0] && arg[0] != LABEL_CHAR)
		process_valid_arg(arg, &i, 1, env);
	else
		return ;
	arg[i] ? asm_error(9, env, 0) : 0;
}
