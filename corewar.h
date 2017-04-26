/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 01:02:31 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/26 03:17:19 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
# define REG_SIZE				4
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
** booleans define
*/

# define TRUE					1
# define FALSE					0

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
** Redcodes define
*/

# define LIVE	0x01
# define LD		0x02
# define ST		0x03
# define ADD	0x04
# define SUB	0x05
# define AND	0x06
# define OR		0x07
# define XOR	0x08
# define ZJMP	0x09
# define LDI	0x0a
# define STI	0x0b
# define FORK	0x0c
# define LLD	0x0d
# define LLDI	0x0e
# define LFORK	0x0f
# define AFF	0x10

/*
** 1) REG_NUMBER registries, each of which are the size REG_SIZE octets.
** A registry is a small memory “box” with only one value
** 2) carry : 1 if the last redcode was sucessfully executed
** 3) live : if the process is alive
** 4) coreid : to which player (core) it belongs
** 5) pc : index in the memory
** 6) how long before executing the next instruction
*/

typedef struct			s_proc
{
	unsigned int		reg[REG_NUMBER];
	int					carry;
	int					live;
	int					coreid;
	int					pc;
	int					cycle_wait;
	struct s_proc	  	*next;
}						t_proc;

/*
** magic determine if the file has the right extension
** prog_name is its name.
** comment is for special message (totaly useless)
** prog_size is the size of its code
** id is player nb
** color is player color
*/

# define PROG_NAME_LENGTH			(128)
# define COMMENT_LENGTH				(2048)
# define COREWAR_EXEC_MAGIC			0xea83f3	/* why not */

typedef struct			s_core
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned int		prog_size;
	char				code[COMMENT_LENGTH + 1];// check about this it seems wrong	
	int					id;
	unsigned			color;
}						t_core;

/*
** progs compete inside the Memory Array Redcode Simulator (Mars)
** memory is our corewar map (instructions)
** memory_color is our corewar map (belong to coreid)
** pc is the index in the memory (max MEM_SIZE).
** nb_process is the nb_process alive
** flags are our options stored on 32 bits (1 per bit : COREWAR_FLAGS)
** players is the nb of player
** t_core has information for each player, on stack
*/

typedef struct			s_vm
{
	unsigned char		memory[MEM_SIZE];
	unsigned char		memory_color[MEM_SIZE];
	int					dump;
	int					nb_process;
	int					flags;
	int					players;
	t_core				core[MAX_PLAYERS];
	int					cycle;
	int					cycle_to_die;
	t_proc				*proc;
}						t_vm;

/*
** flags list
*/

# define COREWAR_FLAGS 			"mgpvc"
# define F_MUSIC				1
# define F_GRAPHIC_DISPLAY		2
# define F_DISPLAY_PLAYERS		4
# define F_DISPLAY_MEM			8
# define F_DISPLAY_CYCLES		16

/*
** parsing options
*/

void			get_args(int ac, char **av, t_vm *vm, int i);
void			get_core(char **av, int n, int i, t_vm *vm);
int				parse_flag(char *s, int *flags);
int				flag_index(char *s, int c);
void			init_cores(t_vm *vm, int i);

/*
** the fight begins
*/

void			core_war(t_vm *vm);
void			get_proc_redcode(t_vm *vm, t_proc **proc);
void			fetch(t_vm *vm, t_proc *proc, int redcode);
void			rc_cost(int *cycle_wait, int redcode);
int				kill_proc(t_vm *vm, t_proc **proc);

/*
** display functions & bonus functions
*/

void			display_memory(t_vm *vm, int n);
void			display_players(t_vm *vm);
void			play_music();

/*
** redcode functions
*/

void			rc_live(t_vm *vm, t_proc *proc);
void			rc_ld(t_vm *vm, t_proc *proc, int redcode);
void			rc_st(t_vm *vm, t_proc *proc);
void			rc_add_sub(t_vm *vm, t_proc *proc, int plus_minus);
void			rc_binary(t_vm *vm, t_proc *proc, int redcode);
void			rc_zjmp(t_vm *vm, t_proc *proc);
void			rc_ldi(t_vm *vm, t_proc *proc, int redcode);
void			rc_sti(t_vm *vm, t_proc *proc);
void			rc_fork(t_vm *vm, t_proc *proc, int redcode);
void			rc_aff(t_vm *vm, t_proc *proc);		

/*
** future includes in libft
*/

unsigned int	ft_endian(unsigned int n);
int				check_arg(unsigned char type, char a1, char a2, char a3);

/*
** error handling
*/

long			errors(int id, char *comment);

#endif
