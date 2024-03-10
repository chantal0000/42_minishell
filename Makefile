# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:53:41 by kbolon            #+#    #+#              #
#    Updated: 2024/03/10 10:47:18 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c \
		src/parser.c \
		src/parser2.c \
		src/parser3.c \
		src/parser4.c \
		src/utils.c
		
LIBFT = libft/libft.a
CC = cc
OBJS = $(SRCS:.c=.o)
#LINUX
#CFLAGS = -Wall -Wextra -Werror -ledit
#COMFLAGS = -I/Users/$(USER)/.brew/opt/readline/include
#LINKFLAGS = -L/Users/$(USER)/.brew/opt/readline -lreadline

#MACOS
CFLAGS = -Wall -Wextra -Werror#could be -leditline
COMFLAGS = -I/opt/homebrew/opt/readline/include#libedit/include
LINKFLAGS = -L/opt/homebrew/opt/readline -lreadline#libedit/lib -ledit

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