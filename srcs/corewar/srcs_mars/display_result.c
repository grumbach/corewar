/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 18:28:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/20 17:54:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	init_var(char **color, char **colorpc, t_mars *vm)
{
	color[0] = 0;
	color[1] = KGRN;
	color[2] = KBLU;
	color[3] = KYEL;
	color[4] = KRED;
	color[5] = KMAG;
	color[6] = KCYN;
	color[7] = KWHT;
	colorpc[0] = 0;
	colorpc[1] = KGRNPC;
	colorpc[2] = KBLUPC;
	colorpc[3] = KYELPC;
	colorpc[4] = KREDPC;
	colorpc[5] = KMAGPC;
	colorpc[6] = KCYNPC;
	colorpc[7] = KWHTPC;
	vm->len_buff = 0;
	vm->index_buff = 0;
}

void		add_vm(t_mars **vm, char *str)
{
	int		i;
	t_mars	*tmp;

	tmp = *vm;
	i = 0;
	while (str[i])
	{
		tmp->buff[tmp->index_buff++] = str[i++];
		(*vm)->len_buff++;
	}
	tmp->buff[tmp->index_buff] = 0;
}

static void	add_vm_nb_hexa(t_mars **vm, unsigned int nb)
{
	char	nb2[2];

	if (nb >= 16)
		add_vm_nb_hexa(vm, nb / 16);
	if (nb % 16 >= 10)
	{
		nb2[0] = nb % 16 - 10 + 'a';
		nb2[1] = 0;
		add_vm(vm, nb2);
	}
	else
	{
		nb2[0] = nb % 16 + '0';
		nb2[1] = 0;
		add_vm(vm, nb2);
	}
}

static void	add_vm_nb_ten(t_mars **vm, unsigned int nb)
{
	char	*str;

	str = ft_itoa(nb);
	add_vm(vm, str);
	free(str);
}

void		add_vm_nb(t_mars **vm, unsigned int nb,
							int base)
{
	if (base == 10)
		add_vm_nb_ten(vm, nb);
	else if (base == 16)
	{
		if (nb == 0)
			add_vm(vm, "00");
		else if (nb < 16)
		{
			add_vm(vm, "0");
			add_vm_nb_hexa(vm, nb);
		}
		else
			add_vm_nb_hexa(vm, nb);
	}
	base == 16 ? add_vm(vm, " ") : nb++;
}


/*
** display on terminal the VM
** then checks processus inside the vm to find the one whose uid is the last
** one alive. Display it.
*/

void	display_winner(t_mars *vm, t_process *cpu)
{
	t_process	*lst;

	display_vm(&vm, cpu);
	vm->nb_process = 0;
	lst = cpu;
	while (lst && lst->uid != vm->last_uid_alive)
		lst = lst->next;
	ft_printf("\nWinner is %s in %d cycles.\n", lst->name, vm->cycle);
}

/*
** JGB functions
*/

static void	add_top_vm(t_mars **vm)
{
	add_vm(vm, "===============================");
	add_vm(vm, "===============================");
	add_vm(vm, "===============================");
	add_vm(vm, "===============================");
	add_vm(vm, "===============================");
	add_vm(vm, "=========");
	add_vm(vm, "===============================\n");
	add_vm(vm, "||");
}

void		add_bottom_vm(t_mars **vm)
{
	add_vm(vm, "\033[0m");
	add_vm(vm, "||");
	add_vm(vm, "\n===============================");
	add_vm(vm, "==============================");
	add_vm(vm, "==============================");
	add_vm(vm, "==============================");
	add_vm(vm, "==============================");
	add_vm(vm, "============================================\n");
	add_vm(vm, "Cycles : ");
	add_vm_nb(vm, (*vm)->cycle, 10);
	add_vm(vm, " Cycles to die : ");
	add_vm_nb(vm, (*vm)->cycle_to_die, 10);
	add_vm(vm, " Process : ");
	add_vm_nb(vm, (*vm)->nb_process, 10);
	add_vm(vm, "\n");
}

static int	it_is_pc(t_process *lst_process, int i)
{
	t_process	*tmp;

	tmp = lst_process;
	while (tmp)
	{
		if (tmp->pc == i && tmp->nb_live != -1)
			return (tmp->color);
		tmp = tmp->next;
	}
	return (0);
}

static void	add_color(t_mars **vm, t_process *lst_process,
						int *i1, int *indpc)
{
	int		i;

	i = *i1;
	if ((*indpc = it_is_pc(lst_process, i)))
		add_vm(vm, g_colorpc[*indpc]);
	else if ((*vm)->memory_color[i] == 0)
		add_vm(vm, "\033[0;1;30m");
	else if ((*vm)->memory_color[i] > 0)
		add_vm(vm, COLOR_PLAYER((*vm)->memory_color[i]));
	else if ((*vm)->memory_color[i] < 0)
	{
		add_vm(vm, "\033[1m");
		add_vm(vm, COLOR_PLAYER(-(*vm)->memory_color[i]));
	}
	add_vm_nb(vm, (*vm)->memory[i], 16);
	add_vm(vm, "\033[0m");
}

void		display_vm(t_mars **vm, t_process *cpu)
{
	int		i;
	int		j;
	int		indpc;

	i = 0;
	j = 0;
	indpc = 0;
	(*vm)->index_buff = 0;
	(*vm)->len_buff = 0;
	add_top_vm(vm);
	while (i < MEM_SIZE)
	{
		add_color(vm, cpu, &i, &indpc);
		if (j == 63 && i != MEM_SIZE - 1)
			add_vm(vm, "\033[0m||\n||");
		j == 63 ? j = 0 : ++j;
		++i;
	}
	add_bottom_vm(vm);
	(*vm)->modif = FALSE;
	system("clear");
	write(1, (*vm)->buff, (*vm)->len_buff);
	usleep(95000);
}
