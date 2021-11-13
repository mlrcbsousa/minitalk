# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2021/11/13 21:57:05 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
LINKS		= -Llibft -lft
CC			= gcc
RM			= rm -f
INC			= -Iincludes -Ilibft
OBJ			= ${SRC:.c=.o}
SRC			= srcs/server.c srcs/client.c
BIN			= server client

NAME		= minitalk

${NAME}:	server client

server:		srcs/server.o
					${MAKE} -C libft
					${CC} ${CFLAGS} srcs/$@.o ${LINKS} -o $@

client:		srcs/client.o
					${MAKE} -C libft
					${CC} ${CFLAGS} srcs/$@.o ${LINKS} -o $@

%.o:%.c
					${CC} ${CFLAGS} ${INC} -c $< -o $@
					
all:			${NAME}

style:		${NAME}
					-norminette $$( find . -type f \( -name "*.c" -or -name "*.h" \) )

# test:
# 					valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
# 					--num-callers=20 --track-fds=yes ./${NAME}

clean:
					${MAKE} clean -C libft
					${RM} ${OBJ}

fclean:		clean
					${RM} ${BIN}

re: 			fclean all

.PHONY : 	all clean fclean re bonus
