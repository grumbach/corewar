/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 10:11:56 by plefebvr          #+#    #+#             */
/*   Updated: 2017/05/16 23:08:37 by plefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void			check_arg_type(t_inst *inst, t_op *op, t_env *env, int i)
{
	t_arg	*a;

	a = inst->arg;
	while (a && i < op->nb_arg)
	{
		if (op->arg[i] == 1)
			a->t == 1 ? 0 : asm_error(16, env, a->line);
		if (op->arg[i] == 2)
			a->t == 2 ? 0 : asm_error(16, env, a->line);
		if (op->arg[i] == 3)
			a->t == 1 || a->t == 2 ? 0 : asm_error(16, env, a->line);
		if (op->arg[i] == 4)
			a->t == 4 ? 0 : asm_error(16, env, a->line);
		if (op->arg[i] == 5)
			a->t == 1 || a->t == 4 ? 0 : asm_error(16, env, a->line);
		if (op->arg[i] == 6)
			a->t == 2 || a->t == 4 ? 0 : asm_error(16, env, a->line);
		if (op->arg[i] == 7)
			a->t == 1 || a->t == 2 || a->t == 4 ? 0 :
				asm_error(16, env, a->line);
		a = a->next;
		i++;
	}
}
