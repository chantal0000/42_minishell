/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 10:58:52 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
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

extern int	g_signal;

# define MAXARGS 100
# define MAX_CONTENT_SIZE 1000

typedef struct s_cmd t_cmd;
typedef struct s_env t_env;

typedef struct s_minishell {
	t_env	*env_list;
	int		og_stdin;
	int		og_stdout;
}	t_minishell;

typedef struct s_env
{
	char	*cmd_env;
	t_env	*next;

}	t_env;

typedef struct s_cmd
{
	int		index;
	t_env	*m_env;
	int		token;
	int		token_env;
	char	*cmd[MAXARGS + 1];
	char	*file_name;
	int		instructions;
	int		fd_in;
	int		fd_out;
	int		pid;
	t_cmd	*prev;
	t_cmd	*next;
	char	*heredoc_delimiter;
}	t_cmd;

// TESTING
void	print_stack(t_cmd *root);

//builtins_error.c
int		ft_handle_error_export(t_cmd *cmd);
int		ft_handle_error_cd(t_cmd *cmd);

//builtins/builtins.c
int		ft_strcmp(char *s1, char *s2);
int		ft_is_builtin(t_cmd *cmd, t_minishell *minishell_struct);

//builtins/ft_cd.c
int		ft_array_size(char **array);
int		ft_cd(t_cmd *cmd);

//ft_echo.c
//int		ft_count(char **arr); same as ft_array_size
int		ft_echo(t_cmd *cmd);
void	ft_putstr(char *s);
void	ft_write_echo(char **arr, int i);

//builtins/env.c
int		ft_env(t_cmd *cmd, t_env **env_list);

//builtins/exit.c
void	ft_handle_nodigi(t_cmd *cmd, t_env *env_list);
int		ft_exit(t_cmd *cmd, t_minishell *minishell_struct);

//builtins/export.c
int		ft_unset_for_export(char *var_name, t_env **env_list);
int		check_for_equal(char *str);
int		ft_check_syntax(char *str);
void	ft_export_print(t_env *temp);
int		ft_export(t_cmd *cmd, t_env **env_list);

//builtins/pwd.c
int		ft_pwd(void);

//builtins/unset.c
int		ft_len_until_delimiter(char *str);
int		find_match(t_env *current, char *str);
void	handle_unset(t_env *current, t_env *prev, t_env **env_list);
int		ft_unset(t_cmd *cmd, t_env **env_list);

//errors/error_handling.c
void	error_temp(char *str, char *temp);
void	error_general(char *str);

//executor/main_utils.c
t_cmd	*first_node(t_cmd *node);
void	ft_reset_std(int std_in, int std_out);
void	ft_start_exec(t_env *env_list, t_cmd *node);

//executor/executor_pipes.c
int		ft_exit_free(t_minishell *minishell_struct, t_cmd *node, int exit_status);
int		ft_pipe_first(t_cmd *node, int pipe_fd[2],
			t_minishell *minishell_struct);
int		ft_pipe_middle(t_cmd *node, int pipe_fd[2], int old_p_in,
			t_minishell *minishell_struct);
int		ft_pipe_last(t_cmd *node, int pipe_fd[2], int old_p_in,
			t_minishell *minishell_struct);

//executor/executor_utils.c
char	*get_command_path(char *cmd, char **path);
char	*find_cmd_path(char *cmd, char **env);
int		execute_cmd(char **env, char **cmd);

//executor/executor.c
int		handle_exit_simple_cmd(t_cmd *node, int exit_status);
int		ft_simple_cmd(t_cmd *node, int exit_status, t_minishell *minishell_struct);
int		loop_cmds(t_cmd *node, t_cmd *head, t_minishell *minishell_struct);
int		ft_executor(t_cmd *node, t_minishell *minishell_struct);

//executor/exit_statuc.c
t_cmd	*last_node(t_cmd *node);
int		count_nodes(t_cmd *node);
int		handle_exit_status(t_cmd *node);

//executor/list_into_arr_env.c
int		ft_list_size(t_env *head);
char	**ft_env_list_to_array(t_env *head);

//executor/set_pipes_utils.c
void	ft_set_pipes_first(t_cmd *node, int pipe_fd[2]);
void	ft_set_pipe_middle(t_cmd *node, int pipe_fd[2], int old_p_in);
void	ft_set_pipe_last(t_cmd *node, int pipe_fd[2], int old_p_in);

//parsing/delimiter.c
int		find_delimiter(char *s1, char *delim);
void	check_quotes(char *s);
void	quote_helper(char *s, int quote, size_t i, size_t len);

//parsing/find_tokens.c
int		check_for_alligators(char **s);
int		find_tokens(char **s, char **beg_of_file);
int		is_token(char s);
int		is_whitespace(char s);int	check_next_char(char **s, char token);

//parsing/init_struct.c
t_cmd	*ft_init_struct(void);
t_cmd	*m_lstlast(t_cmd *lst);
void	m_lstadd_back(t_cmd **lst, t_cmd *new);
void	update_fd(t_cmd *tree);

//parsing/parse_for_cmds.c
void	parse_for_cmds(t_cmd **cmd, char *s);
int		check_for_hanging_pipes(char *s);
int		check_redirection_file_names(char *s);
char	*check_for_quotes(char *s);
char	ft_replace(char *c);

//parsing/parse_environ_variables.c
int		valid_name(char *s);
char	*find_var_position(char *s);
char	*find_substitution(char *s, t_env *env);

//parsing/parse_exec_cmds.c
char	*parse_line(char *arr);
t_cmd	*init_exec_cmds(t_cmd *cmd_tree, char **s, char *non_token);
t_cmd	*parse_exec_cmds(char **s);

//parsing/parse_expansions.c
void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int *exit_status);
void	update_string(char **s, char *var_value, char *second_s);
void	expand_variables(char **s, t_env *env);
void	expand_exit_status(char **s, int *exit_status);
char	*expanded_string(char *first, char *expansion, char *second);

//parsing/parse_for_heredocs.c
void	ft_create_temp_file(char **heredoc_content, t_cmd *cmd);
void	write_heredoc(char **heredoc_content, t_cmd *cmd, char *temp_file);
void	ft_heredoc(t_cmd *cmd, char *file_name);
char	*make_string(char **s);

//parsing/parse_pipes.c
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe);
void	pipe_found_fcn(t_cmd **cmd, char **str);
void	restore_pipes_and_spaces(t_cmd *cmd);
void	ft_restore(char *s);

//parsing/parse_quotes.c
void	remove_quotes(char *str);
void	check_in_cmd_array_for_quotes(char *s);

//parsing/parse_for_redir.c
t_cmd	*parse_for_redirections(t_cmd *node, char **s);
t_cmd	*parse_mult_redir(t_cmd *cmd, char **s, char *filename, int token);
t_cmd	*parse_outfile(t_cmd *node, char **s, char *file_name, int token);
t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd);
int		check_access_and_fd(t_cmd *cmd, int fd_in, int fd_out);

//signals/signals.c
void	ft_ctrl_c_signals(int sig);
void	ft_init_signals(void);
void	ft_ctrl_c_signals_input(int sig);
void	ft_quit_signals_input(int sig);
void	ft_init_signals_input(void);

//signals/signals_heredoc.c
void	ft_init_signals_heredoc(int sig);

//environment.c
void	*create_env_node(char *line);
void	insert_end(t_env **head, char *line);
t_env	*fill_env_struct(char **environment);

//free_functions.c
void	free_memory(char **arr);
void	free_env(char **env);
void	ft_free_env_list(t_env **env_list);
void	ft_free_cmd_struct(t_cmd *cmd);

//main.c
void		ft_execute(char *line, t_cmd **list, t_minishell *minishell_struct, int *exit_status);
char		*read_command(t_cmd *list, t_minishell *minishell_struct , int *exit_status);
void		handle_exit(t_env *env_list, char *line);
t_minishell	*init_minishell(char **env);

//utils.c
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strstr(char *str, char *to_find);

#endif
