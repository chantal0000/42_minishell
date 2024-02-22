# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:53:41 by kbolon            #+#    #+#              #
#    Updated: 2024/02/21 15:13:33 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c \
		src/parser.c
		
LIBFT = libft/libft.a
CC = cc -g
OBJS = $(SRCS:.c=.o)
COMFLAGS = -I/Users/$(USER)/.brew/opt/readline/include
LINKFLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

#MACOS
#CFLAGS = -Wall -Wextra -Werror -ledit#could be -leditline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	cc $(CFLAGS) $(LINKFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(COMFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re