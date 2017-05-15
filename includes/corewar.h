/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 01:02:31 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/15 04:53:43 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <ncurses.h>

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1 // 0b01
# define DIR_CODE				2 // 0b10
# define IND_CODE				3 // 0b11

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8// peut etre a virer ?

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
# define SLEEP					vm->speed//

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define SUDDEN_DEATH			4
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** booleans define
*/

# define TRUE					1
# define FALSE					0

typedef struct			s_vm t_vm;

/*
** 1) REG_NUMBER registries, each of which are the size REG_SIZE octets.
** A registry is a small memory “box” with only one value
** 2) carry : 1 if the last redcode was sucessfully executed
** 3) live : if the scv is alive
** 4) coreid : to which player (core) it belongs
** 5) pc : index in the memory
** 6) how long before executing the next instruction
*/

typedef struct			s_scv
{
	uint				reg[REG_NUMBER + 1];
	uint				pc;
	int					carry;
	int					live;
	int					cooldown;
	struct s_scv	  	*next;
}						t_scv;

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
	uint		prog_size;
	uint		id;
	uint		color;
	char		prog_name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	char		code[COMMENT_LENGTH + 1];// check about this it seems wrong
}						t_core;

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

typedef struct			s_rc
{
	void				(*func)(t_vm*, t_scv*);
	int					arg_max;
	int					arg[3];
	int					cooldown;
	int					octal;
	int					dir_size;
}						t_rc;

/*
** progs compete inside the Memory Array Redcode Simulator (Mars)
** memory is our corewar map (instructions)
** creep is our colored (player's ownership) corewar map (belong to coreid)
** pc is the index in the memory (max MEM_SIZE).
** nb_scv is the nb_scv alive
** flags are our options stored on 32 bits (1 per bit : COREWAR_FLAGS)
** players is the nb of player
** t_core has information for each player, on stack
** n is bytes per row
** https://www.gnu.org/software/guile-ncurses/manual/html_node/
**		Getting-characters-from-the-keyboard.html
*/

# define	KEY_ESCAPE	27
# define	KEY_PLUS	43
# define	KEY_MINUS	45
# define	KEY_SPACE	32

typedef struct			s_curse
{
	WINDOW 				*win;
	int					y;
	int					x;
	int					n;
	int					speed;
	int					key;
	char				pause;
}						t_curse;

typedef struct			s_vm
{
	t_scv				*scv;
	int					nb_scv;
	int					flags;
	int					nb_players;
	int					cycle;
	int					cycle_to_die;
	int					checks;
	uint				last_id_alive;
	int					last_check_live;
	int					nb_total_live;
	int					dump;
	int					redcode;
	t_rc				rc[17];
	uint				arg[3];
	unsigned char		type[3];
	t_curse				curse;
	unsigned char		memory[MEM_SIZE];
	unsigned char		creep[MEM_SIZE];
	t_core				core[MAX_PLAYERS];
}						t_vm;

/*
** flags list
*/

# define COREWAR_FLAGS 			"mv"
# define F_MUTE					1
# define F_VISUAL				2

/*
** parsing options
*/

void			parsing(int ac, char **av, t_vm *vm, int i);
void			get_core(char **av, int n, int i, t_vm *vm);
int				parse_flag(char *s, int *flags);
int				flag_index(char *s, int c);
void			init_cores(t_vm *vm, int i);
void			init_scv(t_vm *vm);

/*
** virtual machine
*/

void			gl_hf(t_vm *vm);
void			reset_cycle(t_vm *vm);

/*
** scvs functions
*/

t_scv			*new_scv(void);
void			kill_dead_scvs(t_vm *vm);
void			kill_all_scvs(t_vm *vm);

/*
** display functions
*/

void			display_winner(t_vm *vm);
void			dump_memory(t_vm *vm);
void			curse_init(t_vm *vm);
void			curse_color(t_vm *vm, t_scv *scv, int scv_position, int color);
void    		curse_memory(t_vm *vm);
void			curse_putchar_log(uint c);
void			curse_putstr_log(char *s);

/*
** sound functions
*/

void			play_music();
int				play_foam(void);

/*
** redcode functions
*/

void			rc_live(t_vm *vm, t_scv *scv);
void			rc_ld(t_vm *vm, t_scv *scv);
void			rc_st(t_vm *vm, t_scv *scv);
void			rc_add(t_vm *vm, t_scv *scv);
void			rc_sub(t_vm *vm, t_scv *scv);
void			rc_and(t_vm *vm, t_scv *scv);
void			rc_or(t_vm *vm, t_scv *scv);
void			rc_xor(t_vm *vm, t_scv *scv);
void			rc_zjmp(t_vm *vm, t_scv *scv);
void			rc_ldi(t_vm *vm, t_scv *scv);
void			rc_sti(t_vm *vm, t_scv *scv);
void			rc_fork(t_vm *vm, t_scv *scv);
void			rc_lld(t_vm *vm, t_scv *scv);
void			rc_lldi(t_vm *vm, t_scv *scv);
void			rc_lfork(t_vm *vm, t_scv *scv);
void			rc_aff(t_vm *vm, t_scv *scv);

/*
** utils
*/

long			errors(int id, char *comment);
unsigned int	endianize(unsigned int n);
uint            mutate(t_vm *vm, t_scv *scv, uint raw, unsigned char type);
int				check_arg(unsigned char type, char a1, char a2, char a3);

#endif
