# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:53:41 by kbolon            #+#    #+#              #
#    Updated: 2024/04/03 16:10:21 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c \
		src/find_tokens.c \
		src/init_struct.c \
		src/parse_exec_cmds.c \
		src/parse_for_cmds.c \
		src/parse_pipes.c \
		src/parse_for_redirs.c \
		src/utils.c \
		src/executor/executor.c \
		src/executor/executor_utils.c \
		src/executor/exit_status.c \
		src/environment.c

LIBFT = libft/libft.a
CC = cc
OBJS = $(SRCS:.c=.o)
#LINUX
#CFLAGS = -Wall -Wextra -Werror
#COMFLAGS = -I/Users/$(USER)/.brew/opt/readline/include
#LINKFLAGS = -L/Users/$(USER)/.brew/opt/readline -lreadline

#MACOS
CFLAGS = -Wall -Wextra -Werror#could be -leditline
COMFLAGS = -I/opt/homebrew/opt/readline/include#libedit/include
LINKFLAGS = -L/opt/homebrew/opt/readline -lreadline#libedit/lib -ledit
#
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
