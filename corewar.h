/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 01:02:31 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/22 20:06:38 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <errno.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
// # define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4096)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** options
*/

# define GRAPHIC				1
# define MUSIC					2
 

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3 /* why not */

/*
** progs compete inside the Memory Array Redcode Simulator (Mars)
** memory is the map where cores compete
** flags on each bit: g for graphic, m for music etc.
*/

# define COREWAR_FLAGS "mg"

typedef struct			s_pc
{
	unsigned int		reg[REG_NUMBER];
	int					carry;
	int					pc;
	int					last_live;
	int					coreid;
}						t_pc;

typedef struct			s_core
{
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned int		prog_size;
	int					id;
}						t_core;

typedef struct			s_vm
{
	unsigned char		memory[MEM_SIZE];
	int					dump;
	int					nb_process;
	int					flags;
	int					players;
	t_core				core[MAX_PLAYERS];

}						t_vm;

long		errors(int id, char *comment);
void		get_args(int ac, char **av, t_vm *vm);
void		core_war(t_vm *vm);




#endif
