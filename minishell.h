/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 19:00:35 by kbolon           ###   ########.fr       */
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
# define MAXARGS 15

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
//	char	*s;
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

//find_tokens.c
int		check_for_alligators(char **s);
int 	find_tokens(char **s, char **beg_of_file, char **end_of_file);
int		check_for_nontokens(char **s);

//nul_terminate_fcns.c
//t_exec	*ft_exec_cmd(t_cmd *cmd);//already null terminate in parse_exec
t_cmd	*ft_nul_cmds(t_cmd *cmd);

//parse_exec_cmds.c
t_cmd	*parse_exec(char **s, t_exec *cmd_tree, char *cmd, char *opt);
t_cmd	*build_cmd_tree(char **s);

//parse_for_cmds.c
t_cmd	*parse_for_cmds(char *s);
int		is_token(char s);
int		is_whitespace(char s);
int		check_next_char(char **s, char token);

//parse_for_redir.c
t_cmd	*parse_for_redirections(t_cmd *cmd, char **s);
t_cmd	*redir_cmd(t_cmd *cmd, char *beg_file, char *end_file, int instructions, int fd);

//parse_pipes_and_groups.c
t_cmd	*parse_for_pipe(char **str);
t_cmd	*parse_for_groups(char **s);
//t_cmd 	*pipe_cmd (t_cmd *left, t_cmd *right);

//utils.c
void	free_cmd_tree(t_exec *tree);
void	free_cmd(t_cmd *cmd);

//char	*ft_strtok(char *str, char *delimiter);
#endif