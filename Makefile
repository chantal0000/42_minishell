# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:53:41 by kbolon            #+#    #+#              #
#    Updated: 2024/04/28 13:05:02 by kbolon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c \
		src/parsing/delimiter_expansions.c \
		src/parsing/expansions.c \
		src/parsing/find_tokens.c \
		src/parsing/init_struct.c \
		src/parsing/parse_echo_awk.c \
		src/parsing/parse_exec_cmds.c \
		src/parsing/parse_for_cmds.c \
		src/parsing/parse_for_redirs.c \
		src/parsing/parse_pipes.c \
		src/free_functions.c \
		src/utils.c \
		src/executor/executor.c \
		src/executor/executor_utils.c \
		src/executor/exit_status.c \
		src/environment.c \
		src/executor/lst_into_arr_env.c \
		src/builtins/builtins.c \
		src/builtins/ft_env.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_export.c \
		src/builtins/ft_unset.c \
		src/builtins/builtins_error.c \
		src/signals/signals.c

LIBFT = libft/libft.a
CC = cc
OBJS = $(SRCS:.c=.o)
#LINUX
#CFLAGS = -Wall -Wextra -Werror
#COMFLAGS = -I/Users/$(USER)/.brew/opt/readline/include
#LINKFLAGS = -L/Users/$(USER)/.brew/opt/readline -lreadline

#MACOS
CFLAGS = -Wall -Wextra -Werror -ggdb3 #could be -leditline
COMFLAGS = -I/opt/homebrew/opt/readline/include#libedit/include
LINKFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline#libedit/lib -ledit
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
