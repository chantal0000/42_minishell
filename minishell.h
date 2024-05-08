/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/08 17:20:56 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int	g_signal;

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
//MACOS
//# include <editline/readline.h>
//# include <histedit.h>
//Linux
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

# define DELIMITER "|<>()"
# define WHITESPACE " \n\t\r\v"
# define MAXARGS 100
# define MAX_CONTENT_SIZE 1000

typedef struct s_cmd t_cmd;
typedef struct s_env t_env;
typedef struct s_exp t_exp;

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
	char	*cmd_env;
	t_env	*next; // pointer to the next node in the linked list

}	t_env;

typedef struct s_exp
{
	char	*exp_name;
	char	*exp_value;
	t_exp	*next;
}	t_exp;


typedef struct s_cmd
{
	int		index;
	t_env	*m_env;
	t_exp	*exp;
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

//delimiter.c
int		find_delimiter(char *s1, char *delim);
char	*check_quotes(char *s);

//find_tokens.c
int		check_for_alligators(char **s);
int		find_tokens(char **s, char **beg_of_file);

//init_struct.c
t_cmd	*ft_init_struct(void);
t_cmd	*m_lstlast(t_cmd *lst);
void	m_lstadd_back(t_cmd **lst, t_cmd *new);
void	update_fd(t_cmd *tree);

//parse_echo_awk.c
void	parse_for_echo(t_cmd *cmd_tree);
int		ft_count(char **arr);
void	ft_echo(t_cmd *cmd);

//parse_exec_cmds.c
char	*parse_line(char *arr);
t_cmd	*init_exec_cmds(t_cmd *cmd_tree, char **s, char *non_token);
t_cmd	*parse_exec_cmds(char **s);

//parse_for_cmds.c
void	parse_for_cmds(t_cmd **cmd, char *s);
int		is_token(char s);
int		is_whitespace(char s);
int		check_next_char(char **s, char token);
char 	*check_for_quotes(char *s);

//parse_for_expanders.c
char	*ft_var_name(char *s, t_exp *exp);
char	*parse_for_duplicate_names(t_exp *exp, char *s, size_t cmd_len);
char	*check_for_question_mark(char *s);
char	*parse_string_for_expansions(char *s, t_exp *exp, int exit_status);
void	parse_cmds_for_expansions(t_cmd **cmd, t_exp *exp, int exit_status);

//parse_for_redir.c
//not checked for long functions and notes
t_cmd	*parse_for_redirections(t_cmd *node, char **s);
t_cmd	*parse_multiple_redirections(t_cmd *cmd, char **s, char *filename, int token);
t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd);
int		ft_open_fcn(t_cmd *node, int instructions, int num);
void	ft_create_temp_file(char **heredoc_content, t_cmd *cmd);
void	ft_heredoc(t_cmd *cmd, char * file_name);
char	*make_string(char **s);

//parse_for_variable_exp.c
//not checked for long functions and notes
t_exp	*insert_exp(t_exp *head, char *name, char *value);
int		search_string_for_equal(char *s);
char	*find_name(char **s);
char	*find_value(char **s);
void	parse_for_variables(t_exp **exp, char **s);

//parse_pipes_and_groups.c
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, int *index);
void	restore_pipes_and_spaces(t_cmd *cmd);
void	ft_restore(char *s);

//free_functions.c
//void	free_cmdtree(t_cmd *tree);
void	free_memory(char **arr);
void	free_env(char	**env);
void	ft_free_env_list(t_env *env_list);
void	ft_free_cmd_struct(t_cmd *cmd);
void	free_exp(t_exp **exp);

//utils.c
char	*ft_strndup(const char *s, size_t n);
char	**export_split(char	*s);
void	parse_string(char *s);

//heredoc.c
//int	ft_strcmp(const char *s1, const char *s2);

// Executer | executer.c
//void	ft_executor(t_cmd *node);
int		ft_executor(t_cmd *node, t_env *env_list);
void	ft_cmd_last(t_cmd *node, int pipe_fd[2], int old_pipe_in);
void	ft_cmd_middle(t_cmd *node, int pipe_fd[2], int old_pipe_in);
void	ft_cmd_first(t_cmd *node, int pipe_fd[2]);
void	close_after(int std_in, int std_out, int pipe_fd[2]);

//error_handling.c
void	error_message(char *str, int i);

//execute_utils.c
int		execute_cmd(char **env, char **cmd);

//exit_status.c
int		handle_exit_status(t_cmd *node);

//environment.c
void	*create_env_node(char *line);
t_env	*fill_env_struct(char **environment);
char 	**ft_env_list_to_array(t_env *head);


//builtins/builtins.c
int	ft_is_builtin(t_cmd *cmd, t_env *env_list);
int	ft_strcmp(char *s1, char *s2);

//builtins/env.c
int	ft_env(t_env *env_list);
//builtins/cd.c
int	ft_cd(t_cmd *cmd);
//builtins/exit.c
int	ft_exit(t_cmd *cmd, t_env *env_list);
//builtins/pwd.c
int	ft_pwd();
int	ft_export(t_cmd *cmd, t_env *env_list);
void	insert_end(t_env **head, char *line);
int	ft_unset(t_cmd *cmd, t_env *env_list);

int	ft_handle_error_export(t_cmd *cmd);
int	ft_handle_error_cd(t_cmd *cmd);



// signals.c
void	ft_init_signals(void);
void	ft_init_signals_input(void);
void	ft_init_signals_heredoc(int sig);
void	ft_ctrl_c_signals_input(int sig);
#endif
