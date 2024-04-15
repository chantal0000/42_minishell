/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/15 13:48:51 by kbolon           ###   ########.fr       */
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
# include <readline/history.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

# define DELIMITER "|<>()"
# define WHITESPACE " \n\t\r\v"
# define MAXARGS 100
# define MAX_CONTENT_SIZE 1000

typedef struct s_cmd t_cmd;
typedef struct s_env t_env;

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
	char	*cmd_env;
	t_env	*next; // pointer to the next node in the linked list

}	t_env;

typedef struct s_cmd
{
	int		index;
	t_env	*m_env;
	int		token;
	char	*cmd[MAXARGS + 1];
	char	*file_name;
	int		instructions;
	int		fd_in;
	int		fd_out;
	int		pid;
	t_cmd	*prev;
	t_cmd	*next;
	char	*heredoc_delimiter;
	char	*heredoc_content[MAX_CONTENT_SIZE + 1];
}	t_cmd;

void	print_stack(t_cmd *root);

//find_tokens.c
int	check_for_alligators(char **s);
int	find_tokens(char **s, char **beg_of_file);

//init_struct.c
t_cmd	*ft_init_struct(void);
t_cmd	*m_lstlast(t_cmd *lst);
void	m_lstadd_back(t_cmd **lst, t_cmd *new);
void	update_fd(t_cmd *tree);

//parse_exec_cmds.c
char	*parse_line(char *arr);
t_cmd	*init_exec_cmds(char **s, char *non_token);
t_cmd	*parse_exec_cmds(char **s);

//parse_for_cmds.c
void	parse_for_cmds(t_cmd **cmd, char *s, char **env);
int		is_token(char s);
int		is_whitespace(char s);
int		check_next_char(char **s, char token);

//parse_for_redir.c
t_cmd	*parse_for_redirections(t_cmd *node, char **s);
t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd);
void	ft_heredoc(t_cmd *cmd);
char	*make_string(char **s);

//parse_pipes_and_groups.c
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, int *index);
//t_cmd	*parse_for_groups(char **s);
char	parse_for_single_quotes(char *s);
char	*parse_for_quotes(char *s);

//free_functions.c
void	free_cmdtree(t_cmd *tree);
void	free_memory(char **arr);
void	free_env(t_env	**env);

//utils.c
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		find_delimiter(char *s1, char *delim);
char	*check_quotes(char *s);
char	**export_split(char	*s);

void	ft_echo(t_cmd *cmd);

//heredoc.c
//int	ft_strcmp(const char *s1, const char *s2);

// Executer | executer.c
//void	ft_executor(t_cmd *node);
int		ft_executor(t_cmd *node);
void	ft_cmd_last(t_cmd *node, int pipe_fd[2], int old_pipe_in);
void	ft_cmd_middle(t_cmd *node, int pipe_fd[2], int old_pipe_in);
void	ft_cmd_first(t_cmd *node, int pipe_fd[2]);

//execute_utils.c
int		execute_cmd(char **env, char **cmd);

//exit_status.c
int		handle_exit_status(t_cmd *node);

//environment.c
void	*create_env_node(char *line);
void	fill_env_struct(t_cmd *cmd, char **environment);
char 	**ft_env_list_to_array(t_env *head);


//builtins/builtins.c
int	ft_is_builtin(t_cmd *cmd);
int	ft_strcmp(char *s1, char *s2);

//builtins/env.c
int	ft_env(t_cmd *cmd);
//builtins/cd.c
int	ft_cd(t_cmd *cmd);
//builtins/exit.c
int	ft_exit(t_cmd *cmd);
//builtins/pwd.c
int	ft_pwd();
int	ft_export(t_cmd *cmd);

#endif
