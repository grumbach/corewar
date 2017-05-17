# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/04 18:44:23 by angavrel          #+#    #+#              #
#    Updated: 2017/05/17 03:00:48 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################## BIN #############################################

VM_NAME = corewar

ASM_NAME = asm

VM_SRC = \
	scbw_main.c \
	scbw_parse.c \
	scbw_glhf.c \
	scbw_scv.c \
	scbw_dump.c \
	scbw_misc.c \
	scbw_ncurse.c \
	play_music.c \
	rc_logic.c \
	rc_live.c \
	rc_zjmp.c \
	rc_ld.c \
	rc_fork.c \
	rc_st.c \
	rc_aff.c \
	rc_tools.c

ASM_SRC = \
	main.c \
	error.c \
	parse.c \
	utils.c \
	type_of_line.c \
	put_name.c \
	put_comment.c \
	put_label.c \
	put_inst.c \
	get_arg.c \
	arg_syntax.c \
	check_arg_type.c \
	generate_file.c \
	check_label.c \
	header.c \
	write_instruction.c \
	write_process.c \
	free.c \
	tools.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

LIB = -lncurses -Llibft/ -lft

INCLUDES_VM = -Ilibft/includes/ -Iincludes/

INCLUDES_ASM = -Ilibft/includes/ -Iincludes/

DEPVM = includes/corewar.h libft/includes/libft.h libft/includes/ft_printf.h

DEPASM = libft/includes/libft.h includes/op.h includes/asm.h

CC = gcc

VM_OBJ = $(addprefix ${OBJDIR}/, $(VM_SRC:.c=.o))

ASM_OBJ = $(addprefix ${OBJDIR}/, $(ASM_SRC:.c=.o))

############################## COLORS ##########################################

BY = "\033[33;1m"
BR = "\033[31;1m"
BG = "\033[32;1m"
BB = "\033[34;1m"
BM = "\033[35;1m"
BC = "\033[36;1m"
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
M = "\033[35m"
C = "\033[36m"
WT = "\033[37;1m"
W = "\033[0m""\033[32;1m"
WR = "\033[0m""\033[31;5m"
WY = "\033[0m""\033[33;5m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

############################## RULES ###########################################

all: libft ride ${VM_NAME} ${ASM_NAME} unicorn

silent: libft ${VM_NAME} ${ASM_NAME} unicorn

libft: dragon
	@make -C libft/

############################## VM ##############################################

${VM_NAME}: ${VM_OBJ} libft
	@echo ${B}Compiling [${VM_NAME}]...${X}
	@${CC} ${CFLAGS} ${INCLUDES_VM} ${LIB} -o $@ ${VM_OBJ}
	@echo ${G}Success"   "[${VM_NAME}]${X}

${OBJDIR}/%.o: ./srcs/vm/%.c libft ${DEPVM}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} ${INCLUDES_VM} -c -o $@ $<
	@printf ${UP}${CUT}

############################## ASM #############################################

${ASM_NAME}: ${ASM_OBJ} libft
	@echo ${B}Compiling [${ASM_NAME}]...${X}
	@${CC} ${CFLAGS} ${INCLUDES_ASM} ${LIB} -o $@ ${ASM_OBJ}
	@echo ${G}Success"   "[${ASM_NAME}]${X}

${OBJDIR}/%.o: ./srcs/asm/%.c libft ${DEPASM}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} ${INCLUDES_ASM} -c -o $@ $<
	@printf ${UP}${CUT}

############################## GENERAL #########################################

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${VM_NAME}]...${X}
	@/bin/rm -f ${VM_NAME}
	@echo ${R}Cleaning"  "[${ASM_NAME}]...${X}
	@/bin/rm -f ${ASM_NAME}

test:
	@${CC} -g ${INCLUDES_VM} -fsanitize=address ${LIB} \
	-I. -o ${VM_NAME} $(addprefix srcs/vm/, ${VM_SRC})
	@${CC} -g ${INCLUDES_ASM} -fsanitize=address ${LIB} \
	-I. -o ${ASM_NAME} $(addprefix srcs/asm/, ${ASM_SRC})

re: fclean all

build: libft ${VM_OBJ} ${ASM_OBJ}

############################## DECORATION ######################################

unicorn:
	@echo "                              ,|"
	@echo "                             //|                              ,|"
	@echo "                           //,/                             -~ |"
	@echo "                         // / |                         _-~   /  ,"
	@echo "                       /'/ / /                       _-~   _/_-~ |"
	@echo "                      ( ( / /'                   _ -~     _-~ ,/'"
	@echo "                       \\~\\/'/|             __--~~__--\\ _-~  _/,"
	@echo "               "${BB}","${BC}","${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}")"${BG}")"${BY}";"${BR}", "${X}"\\/~-_     __--~~  --~~  __/~  _-~ /"
	@echo "            __"${BB}")"${BC}")"${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}")"${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}")"${BG}";"${WT}",>/\\   /        __--~~  \\-~~ _-~"
	@echo "           "${WT}"-\\\\"${BB}"("${BC}"("${BG}"("${BY}"("${BR}"("${BM}" "${BB}"'"${BC}"'"${BG}"'"${BY}"'"${BR}"("${BM}"("${BB}"("${BC}"("${BG}"("${BY}"("${BR}"("${BM}"( "${WT}">~\\/     --~~   __--~' _-~ ~|"
	@echo "  "${WT}""${BM}"-"${WT}"-"${BM}"="${WT}"=/"${BM}"/"${WT}"/"${BM}"/"${WT}"/"${BM}"/"${BB}"("${BC}"("${BG}""${BY}"'"${BR}"'  "${WT}".     "${BB}"\`"${BC}")"${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}", "${WT}"/     ___---~~  ~~\\~~__--~"
	@echo "          "${BB}")"${BG}")"${BY}"| "${WT}"(@    ;-.    "${BR}"("${BM}"("${BB}"("${BC}"("${BG}"("${WT}"/           __--~~~'~~/"
	@echo "          "${BG}"( "${WT}"\`|    /  )      "${BB}")"${BC}")"${BG}")"${WT}"/      ~~~~~__\\__---~~/ "${BM}","${BB}"("${BC}"("${BG}"("${BY}"("${BR}"("${BB}"("${BC}"("
	@echo "             "${WT}"|   |   |       "${BG}"("${WT}"/      ---~~~/__-----~~\\\\"${BM}")"${BB}")"${BC}")"${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}")"${BG}")"${BY}")"
	@echo "             "${WT}"o_);   ;        /      ----~~/           \\\\"${BC}"("${BG}"("${BY}"("${BR}"("${BM}"("${BB}"("${BC}"("${BG}"("${BY}"("${BR}"("${BM}"("
	@echo "                   "${WT}";        (      ---~~/         \`:::|     "${BC}")"${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}";"${BG}","${BY}"."
	@echo "                  "${WT}"|   _      \`----~~~~'      /      \`:|      "${BY}"("${BR}"("${BM}"("${BB}"("${BC}"("${BG}"("${BY}"("${BR}"("${BM}"("${BB}"("
	@echo "            "${WT}"______/\\/~    |                 /        /         "${BB}")"${BC}")"${BG}")"${BY}")"${BR}")"${BM}")"${BB}")"${BC}")"${BG}")"
	@echo "          "${WT}"/~;;.____/;;'  /          ___----(   \`;;;/                "${BB}")"${BC}")"${BG}")"${BY}")"
	@echo "         "${WT}"/ //  _;______;'------~~~~~    |;;/\\    /                    "${BY}")"${BR}")"
	@echo "        "${WT}"//  | |                        /  |  \\;;,\\"
	@echo "       (<_  | ;                      /',/-----'  _>"
	@echo "        \\_| ||_                     //~;~~~~~~~~~"
	@echo "            \`\\_|                   (,~~"
	@echo "                                    \\~\\"
	@echo "                                     ~~"
	@echo ""${X}

ride:
	@afplay resources/ride.wav&

dragon:
	@echo ""
	@echo ""${X}${BG}
	@echo "	                         "${BB}"     _"${BG} "C"${R}"O"${BY}"R"${BG}"E"${BY}"W"${BR}"A"${BG}"R"
	@echo "	                          "${BB}" "${WT}"=="${BB}"(W"${WT}"{==========-   "${BG}"   /="${WT}"==-"
	@echo "	                           "${BB}"  ||  (.--.)        "${BG}" /="${WT}"==-"${BG}"_---~~~~~~~----__"
	@echo "	                            "${BB}" | \\_,|"${WR}"**"${W}${BB}"|,__   "${BG}"   |="${WT}"==-"${BG}"~___            _,_'"${WT}"'>"
	@echo "	                -=="${BG}"\\\\\\\\      "${BB}"  \`\\ ' \`--'   ),  "${BG}"  \`//~\\\\\\\\   ~~~~\`--._.--"${WT}">"${BG}""
	@echo "	            ______"${WT}"-=="${BG}"|       "${BB}" /\`\\_. .__/\\ \\   "${BG}" | |  \\\\\\\\          _-~\`"
	@echo "	      __--~~~  ,-/"${WT}"-=="${BG}"\\\\\\\\    "${BB}"  (   | .  "${WT}"|~~~~|   "${BG}"| |   \`\\       ,'"
	@echo "	   _-~       /'    |  \\\\\\\\   "${BB}"  )__/==0==-"${WT}"\\42/ "${BG}"  / /      \\     /"
	@echo "	 .'        /       |   \\\\\\\\    "${BB}"  /~\\___/~~"${WT}"\\/ "${BG}" /' /        \\   /"
	@echo "	/  ____  /         |    \\\`\\.__/-~~   \\  |_/'  /          \\/'"
	@echo "	"${WT}"V"${BG}"-'~   "${WT}"v"${BG}"~~~~---__  |     ~-/~         ( )   /'        _--"${WT}"v"${BG}"\`"
	@echo "	                 \\_|      /        _) | ;  ),   __--~~"
	@echo "	                   '~~--_/      _-~/- |/ \\   '-~ \\"
	@echo "	                  "${WT}"{\\\\"${BG}"__~~"${WT}"_/}"${BG}"    / \\\\\\\\_>-|)<__\\      \\"
	@echo "	                  /'   "${WT}"(_/"${BG}"  _-~  | |__>--<__|      |"
	@echo "	                 |   _/"${BR}"-"${BG}"))-~     | |__>--<__|      |"
	@echo "	                 / /~ ,_/       / /__>---<__/      |"
	@echo "	                o-o _//        /-~_>---<__-~      /"
	@echo "	                (^(~          /~_>---<__-      _-~"
	@echo "	               "${WR}","${WY}"/"${WR}"|"${W}"           /__>--<__/     _-~"
	@echo "	            "${WR}",//"${WY}"("${WR}"'("${W}"          |__>--<__|     /                  .--_"
	@echo "	           "${WR}"( "${WY}"( '"${WR}"))"${W}"          |__>--<__|    |                 /' _-_~\\"
	@echo "	          "${WR}"\`-))"${WY}" )"${WR}") ("${W}"         |__>--<__|    |               /'  /   ~\\\`\\"
	@echo "	       "${WR}",/,'"${WY}"//"${WR}"( ("${W}"             \\__>--<__\\    \\            /'  //      ||"
	@echo "	  "${WR}"(( ,( ( "${WY}"((, "${WR}"))"${W}"              ~-__>--<_~-_  ~--__---~'/'/  /'       "${WT}"VV"${BG}
	@echo "	 "${WR}"\\ \`~/  "${WY}")\` )"${WR}" ,/|"${W}"                 ~-_~>--<_/-__      __-~ _/"
	@echo "	 "${WR}"._-~//( "${WY}")/ "${WR}")) \`"${W}"                    ~~-'_/_/ /~~~~~__--~"
	@echo "	  "${WR}" '"${WY}"( ')"${WR}"/ ,)("${W}"                              ~~~~~~~~"
	@echo "	 "${WR}"   ) '( (/"${W}
	@echo ""${X}

.PHONY: all clean fclean re test build ride dragon unicorn
