# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2021/11/18 17:18:35 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
LINKS		= -Llibft -lft
CC			= gcc
RM			= rm -f
INC			= -Iincludes -Ilibft
OBJ			= ${SRC:.c=.o}
SRC			= srcs/server.c srcs/client.c srcs/server_bonus.c srcs/client_bonus.c
BIN			= server client
SERVER	= srcs/server.o
CLIENT	= srcs/client.o

NAME		= minitalk

${NAME}:	${BIN}

server:		srcs/server.o srcs/server_bonus.o
					${MAKE} -C libft
					${CC} ${CFLAGS} ${SERVER} ${LINKS} -o $@

client:		srcs/client.o srcs/client_bonus.o
					${MAKE} -C libft
					${CC} ${CFLAGS} ${CLIENT} ${LINKS} -o $@

%.o:%.c
					${CC} ${CFLAGS} ${INC} -c $< -o $@

all:			${NAME}

bonus: 		SERVER = srcs/server_bonus.o
bonus:		CLIENT = srcs/client_bonus.o
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
