# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 14:30:13 by kbolon            #+#    #+#              #
#    Updated: 2024/02/20 17:18:56 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = src/pipex.c\
		src/pipex_utils.c\

LIBFT = ../libft/libft.a

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	cc ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:
	make -C libft

clean: 
	rm -f ${OBJS}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all 

.PHONY: all clean fclean 