# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <msousa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2021/11/19 16:35:52 by msousa           ###   ########.fr        #
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

${NAME}:	${BIN}

server:		srcs/server.o
					${MAKE} -C libft
					${CC} ${CFLAGS} srcs/server.o ${LINKS} -o $@

client:		srcs/client.o
					${MAKE} -C libft
					${CC} ${CFLAGS} srcs/client.o ${LINKS} -o $@

%.o:%.c
					${CC} ${CFLAGS} ${INC} -c $< -o $@

all:			${NAME}

bonus:		all

style:
					-norminette $$( find . -type f \( -name "*.c" -or -name "*.h" \) )

clean:
					${MAKE} clean -C libft
					${RM} ${OBJ}

fclean:		clean
					${RM} ${BIN}

re: 			fclean all

.PHONY : 	all clean fclean re bonus
