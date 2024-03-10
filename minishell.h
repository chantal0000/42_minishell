/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/10 10:48:08 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
//MACOS
//# include <editline/readline.h>
//Linux
# include <readline/readline.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define DELIMITER "|<>()"
# define WHITESPACE " \n\t\r\v"
# define MAXARGS 10

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	*s;
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	char	*cmd[MAXARGS];
	char	*options[MAXARGS];
}	t_exec;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*beg_file;
	char	*end_file;
	int		instructions;
	int		fd;
}	t_redir;

//parser.c
t_cmd	*parse_for_cmds(char *s);
int		is_token(char s);
int		is_whitespace(char s);
t_cmd	*ft_parse_for_pipe(char **str);
int		check_next_char(char **s, char token);

//parser2.c
int		check_for_alligators(char **s);
int 	find_tokens(char **s, char **beg_of_file, char **end_of_file);
int		check_for_nontokens(char **s);
t_cmd	*ft_nul_cmds(t_cmd *cmd);
t_cmd 	*pipe_cmd (t_cmd *left, t_cmd *right);

//parser3.c
t_cmd	*redir_cmd(t_cmd *cmd, char *beg_file, char *end_file, int instructions, int fd);
t_cmd	*parse_for_groups(char **s);
t_cmd	*parse_exec(char **s, t_exec *cmd_tree, char *cmd, char *opt);
t_cmd	*build_cmd_tree(char **s);
t_cmd	*parse_for_redirections(t_cmd *cmd, char **s);

//parser4.c
t_exec	*ft_exec_cmd(t_cmd *cmd);

//utils.c
void	free_cmd_tree(t_exec *tree);


//char	*ft_strtok(char *str, char *delimiter);

#endif