/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newplayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:14:04 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/20 15:32:28 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			ft_check_live(t_mars **vm, t_process **lst_process)
{
	t_process	*process;
	int			nb_live;

	nb_live = 0;
	process = *lst_process;
	while (process)
	{
		if (process->nb_live < 1)
			process->nb_live = -1;
		else if (nb_live += process->nb_live)
			process->nb_live = 0;
		process = process->next;
	}
	(*vm)->nb_live_check++;
	if (nb_live >= NBR_LIVE || (*vm)->nb_live_check == MAX_CHECKS)
	{
		(*vm)->nb_live_check = 0;
		(*vm)->cycle_to_die -= CYCLE_DELTA;
	}
	(*vm)->last_check_live = 0;
	return (nb_live);
}

static int	get_size(int fd)
{
	int		size;
	int		c;

	size = 0;
	lseek(fd, sizeof(t_core), SEEK_SET);
	while (read(fd, &c, 1) > 0)
		size++;
	lseek(fd, sizeof(t_core), SEEK_SET);
	return (size);
}

int			add_lst(t_process **lst_process, int fd, int uid)
{
	t_process		*process;
	t_process		*tmp;
	static int		color = 1;

	tmp = *lst_process;
	if (!(process = ft_new_process(fd, uid, color)))
		exit(EXIT_FAILURE);
	if ((*lst_process) == NULL)
		(*lst_process) = process;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = process;
	}
	color++;
	return (1);
}

t_process	*ft_new_process(int fd, int uid, int color)
{
	t_process	*new;
	int			i;

	i = 1;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(EXIT_FAILURE);
	new->next = NULL;
	new->nb_live = 0;
	new->pc = 0;
	new->carry = 0;
	new->uid = uid;
	new->cycle_wait = 0;
	new->color = color;
	if (!ft_get_info_process(fd, new))
	{
		free(new);
		return (NULL);
	}
	new->reg[0] = new->uid;
	while (i < 16)
		new->reg[i++] = 0;
	return (new);
}

int			ft_get_info_process(int fd, t_process *process)
{
	ft_bzero(process->name, PROG_NAME_LENGTH);
	lseek(fd, 4, SEEK_SET);
	read(fd, &process->name, PROG_NAME_LENGTH - 4);
	process->size_code = get_size(fd);
	if (process->size_code > CHAMP_MAX_SIZE)
		return (0);
	process->code = (unsigned char *)ft_memalloc(process->size_code);
	read(fd, process->code, process->size_code);
	return (1);
}
