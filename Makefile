# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2021/11/11 21:08:37 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
LINKS		= -Llibft -lft
CC			= gcc
RM			= rm -f
INC			= -Iincludes -Ilibft
OBJ			= ${SRC:.c=.o}
SRC			= srcs/minitalk.c

SERVER	= server.c
client	= client.c

NAME		= minitalk

${NAME}:	server.o client.o ${OBJ}
					${MAKE} -C libft
					${CC} ${CFLAGS} ${OBJ} server.o ${LINKS} -o server
					${CC} ${CFLAGS} ${OBJ} client.o ${LINKS} -o client

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
					${RM} ${NAME}

re: 			fclean all

.PHONY : 	all clean fclean re bonus
