/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/28 11:51:43 by chbuerge         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define DELIMITER "|<>()"
# define WHITESPACE " \n\t\r\v"
# define MAXARGS 5

typedef struct s_cmd t_cmd;
typedef struct s_env t_env;

/*typedef struct s_head
{
	int		index;
	char	**cmd_env;
	t_cmd	*cmd;
}	t_head;*/

typedef struct s_env
{
	char	**cmd_env;
	t_env	*next; // pointer to the next node in the linked list

}	t_env;

/*typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	t_env	*m_env;
	char	*file_name;
	int		instructions;
	int		fd_in;
	int		fd_out;
}	t_redir;*/


typedef struct s_cmd
{
	int		index;
	t_env	*m_env;
	char	*cmd[MAXARGS + 1];
	char	*file_name;
	int		instructions;
	int		fd_in;
	int		fd_out;
	t_cmd	*prev;//pointer to left branch (PIPE)
	t_cmd	*next;//pointer to right branch (PIPE)
} t_cmd;


void	print_stack(t_cmd *root);

//find_tokens.c
int		check_for_alligators(char **s);
int 	find_tokens(char **s, char **beg_of_file);
int		check_for_nontokens(char **s);

//init_struct.c
t_cmd	*ft_init_stuct(void);
t_cmd	*add_node(t_cmd *cmd, t_cmd *next, t_env *env, int index);
t_cmd	*init_redir(t_cmd *cmd_tree, char *file_name, int instructions, int fd);

//parse_exec_cmds.c
char	*parse_line(char *arr);
t_cmd	*init_exec_cmds(char **s, char *non_token);
t_cmd	*parse_exec_cmds(char **s);

//parse_for_cmds.c
void	parse_for_cmds(t_cmd **cmd, char *s);
int		is_token(char s);
int		is_whitespace(char s);
int		check_next_char(char **s, char token);

//parse_for_redir.c
t_cmd	*parse_for_redirections(t_cmd *node, char **s);
t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd);

//parse_pipes_and_groups.c
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe);
t_cmd	*parse_for_groups(char **s);
//t_cmd	*init_pipe(t_cmd *prev, t_cmd *next, int *i);


//utils.c
void	free_cmdtree(t_cmd *tree);



// Executer | executer.c
int		ft_executor(t_cmd *node, char **env);
void	ft_cmd_last(t_cmd *node, int pipe_fd[2], int old_pipe_in);
void	ft_cmd_middle(t_cmd *node, int pipe_fd[2], int old_pipe_in);
void	ft_cmd_first(t_cmd *node, int pipe_fd[2]);

int	execute_cmd(char **env, char **cmd);
int	handle_exit_status(int pid);
#endif
