/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 06:31:39 by angavrel          #+#    #+#             */
/*   Updated: 2017/04/21 23:16:54 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include <libft.h>
#include <ncurses.h>
# include <stdio.h>//

/*
** from op.h file originally made by zaz and assuming that int is on 32 bits
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
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
** added defines
*/

# define DUMP					20
# define SIZE_LINE				64
# define TRUE					1
# define FALSE					0
# define COLOR_PLAYER(player) (color[(int)player])

# define KBLU  "\033[34m"
# define KGRN  "\033[32m"
# define KYEL  "\033[33m"
# define KMAG  "\033[35m"
# define KCYN  "\033[36m"
# define KWHT  "\033[37m"
# define KRED  "\033[31m"

# define KREDPC  "\033[41m"
# define KGRNPC  "\033[42m"
# define KYELPC  "\033[43m"
# define KBLUPC  "\033[44m"
# define KMAGPC  "\033[45m"
# define KCYNPC  "\033[46m"
# define KWHTPC  "\033[47m"

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct			s_xy
{
	int					x;
	int					y;
}						t_xy;

// typedef struct			s_op
// {
// 	char				op[42];
// 	int					a;
// 	int					args[42];
// 	int					b;
// 	char				description[42];
// 	int					c;
// 	int					d;
// }						t_op;

typedef struct			s_core
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_core;

/*
** name : player's name
** reg[0-15] is player's register
** pc : program counter : where we are in the memory between 0 and 4095
** carry : if 0 it jumps, if 1 no jump.
** cycle_wait : each instruction has a cycle count and must wait once executed
** size_code : how many instructions the virus has.
** *code : is the final code in hexa.
** nb_live : every delta (50) cycles it should have live at
** least once and if superior to NBR_LIVE (21) will reset cycle_to_die.
** uid : is the number of the virus linked to player's name.
** color : warrior's color
** next: it is a list so it is the next virus (warrior and its forked warriors)
*/

typedef struct			s_data;		
{
	char				name[128];
	unsigned int		reg[REG_NUMBER];
	short				pc;
	short				carry;
	short				cycle_wait;
	short				size_code;
	unsigned char		*code;
	short				nb_live;
	short				uid;
	unsigned int		color;
}						t_data;

typedef struct			s_virus
{
	t_data				*data;
	struct s_virus		*next;
}						t_virus;

/*
** Legacy : Corewar was originally executed by a virtual machine known as a 
** Memory Array Redcode Simulator, or MARS.
*/

/* 
** memory[MEM_SIZE] is the memory
** memory_color[MEM_SIZE], is the color to display warriors and important events
** we refresh every dump (20) cycles.
** cycle is the total_nb of cycles in the current game
** cycle_to_die : when it reaches 0 game is over or no warriors are still alive
** nb_live_check : check the total nb thhat check lives was called. if over a certain value,
** it is reset to 0 and cycle_to_die -= CYCLE_DELTA (50); 
** last_uid_alive : who was the last warrior alive;
** last_check_live : make sure that during cycles we reached cycle to die.
** last_flush : decides when we refresh the UI with dump 
** modif : when we write in the memory we know that we should update the UI : True or False
** buff[900000] contains colors + instructions.
** len_buff : should we really explain ?
** index_buff : the current position inside the buffer
** nb_virus : nb of virus
** nb_players : numbers of players in the champchionship
** option : for the graphic options
**
*/

typedef struct			s_mars
{
	unsigned char		memory[MEM_SIZE];
	char				memory_color[MEM_SIZE];
	int					dump;
	int					cycle;
	int					cycle_to_die;
	int					nb_live_check;
	int					last_uid_alive;
	int					last_check_live;
	int					last_flush;
	int					modif;
	unsigned char		buff[900000];
	int					len_buff;
	int					index_buff;
	int					nb_virus;
	int					nb_players;
	int					*option;
	t_virus				*virus;
}						t_mars;

/*
** starting with parsing ~ main.c
*/

int      	display_usage(char *s);
int			parse_ac(char **av, int ac, t_mars *vm);
int			parse_flag(char *s, int *flags);
int			get_flags(char **av, int ac, int *option, int i);
int			get_players(char **av, int ac, t_virus *cpu, int i);
int			ft_check_live(t_mars **vm, t_virus **lst_virus);

/*
** (JGB) new player ~ newplayer.c
*/

int			add_lst(t_virus **lst_virus, int fd, int uid);
t_virus	*ft_new_virus(int fd, int uid, int color);
int			ft_get_info_virus(int fd, t_virus *virus);

/*
** init functions ~ init.c
*/

t_mars		*init_vm();
int			get_redcode(char **av, int ac, int *option);
void		init_memory(t_mars **vm);
void	    init_virus(t_mars *vm);


/*
** running the program ~ corewar.c
*/

/*
** 1st function to design :
** start_tournament function : while (vm->virus) 1) refresh cycle, 2) launch
** cpu and 3) check total_nb of lives. 
*/

void    	cw_play(t_mars *vm, t_virus *cpu);
void		run_cpu(t_mars **vm, t_virus **lst_virus);

/*
** warrior parsing functions ~ parsing.c
*/



/*
** check that virus is alive ~ 
*/

int			proc_check_alive();	

/*
** print result of the tournament and free remaining virus.
*/

void		display_winner(t_mars *vm, t_virus *cpu);
void		display_vm(t_mars **vm, t_virus *cpu);
/*
** miscellaneous functions ~ misc.c
*/

void		free_del_virus(t_virus *lst_virus);

#endif
