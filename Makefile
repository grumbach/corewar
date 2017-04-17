# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 00:03:30 by agrumbac          #+#    #+#              #
#    Updated: 2017/04/17 18:35:54 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

ASM_NAME = asm

SRC = corewar.c # op.c

ASM_SRC = asm.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

DEPVM = corewar.h libft/includes/libft.h libft/includes/ft_printf.h

DEPASM = asm.h libft/includes/libft.h

CC = gcc

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

ASM_OBJ = $(addprefix ${OBJDIR}/, $(ASM_SRC:.c=.o))

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

all: ride dragon ${NAME} ${ASM_NAME} unicorn
	@echo ${G}Success"   "[${NAME}]${X}

${NAME}: ${OBJ}
	@make -C libft/
	@echo ${B}Compiling [${NAME}]...${X}
	@${CC} ${CFLAGS} -Ilibft/includes/ -Llibft/ -lft -I. -o $@ ${OBJ}

${ASM_NAME}: ${ASM_OBJ}
	@echo ${B}Compiling [${ASM_NAME}]...${X}
	@${CC} ${CFLAGS} -Ilibft/includes/ -Llibft/ -lft -I. -o $@ ${ASM_OBJ}

${OBJDIR}/%.o : ./srcs/asm/%.c ${DEPASM}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -Ilibft/includes/ -I. -c -o $@ $<
	@printf ${UP}${CUT}

${OBJDIR}/%.o : ./srcs/corewar/%.c ${DEPVM}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -Ilibft/includes/ -I. -c -o $@ $<
	@printf ${UP}${CUT}

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${NAME}]...${X}
	@/bin/rm -f ${NAME}
	@echo ${R}Cleaning"  "[${ASM_NAME}]...${X}
	@/bin/rm -f ${ASM_NAME}

test:
	@${CC} -g -I./libft/includes/ -fsanitize=address -Llibft/ -lft \
	-I. -o ${NAME} $(addprefix srcs/, ${SRC})
#"{BB}" "${BC}" "${BG}" "${BY}" "${BR}" "${BM}"
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
	@echo "          "${BB}")"${BG}")"${BY}"| "${WT}"(@    ;-.     "${BR}"("${BM}"("${BB}"("${BC}"("${BG}"("${WT}"/           __--~~~'~~/"
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
	@echo ""

ride:
	afplay resources/ride.wav&

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
	@echo "	"${WT}"V"${BG}"-'~    "${WT}"v"${BG}"~~~~---__  |     ~-/~         ( )   /'        _--"${WT}"v"${BG}"\`"
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

re: fclean all

build: ${OBJ}

.PHONY: all clean fclean re test panic build
