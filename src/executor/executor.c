/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:35:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/05 14:54:55 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Executes a simple command. If it's a built-in command, it's executed directly.
** Otherwise, it handles redirections and executes using execve().
*/

int	ft_simple_cmd(t_cmd *node, int exit_status, int pid, t_env *env_list)
{
	if ((node->fd_in) != -1)
	{
		printf("fd_in in exec %d \n", node->fd_in);
		dup2(node->fd_in, STDIN_FILENO);
	}
	//next line only added for test purpse pls delete
	node->fd_out = -1;
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	if (ft_is_builtin(node, env_list) == 0)
		return (exit_status);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			// env1 = ft_env_list_to_array(env_list);
			if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
				exit (127);
		}
		else
		{
			waitpid(pid, &exit_status, WUNTRACED);
			return (exit_status);
		}
	}
	// close fd_in??
    // close(original_stdout); // Clo
		// dup(STDOUT_FILENO);// somewhere set back to be stdout?
	return (exit_status);
}

/*
** Handles the execution of the first command in a pipeline.
** Handles input/output redirection and executes the command.
** - 1 meaning there if no in/out file
** 1. if there is an infile we dup the files fd for stdin
** 2. if there is an outfile we dup the files fd for stdout
** 3. else we set the stdout to pipe_fd[1] (write end)
*/
// close read end of new pipe (pipe_fd)
// close std_out
// dup2 stdout into the write end of the pipe
// close write end of pipe
// dup2 stdin in stdin
// close stdin
int	ft_pipe_first(t_cmd *node, int pipe_fd[2], t_env *env_list)
{
	int	pid;

	pid = 0;
	if ((node->fd_in) != -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		// write (2, "dupping IN first pipe\n", 23);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	close(pipe_fd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (ft_is_builtin(node, env_list) == 0)
			exit (0);
		else if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
			exit (127);
	}
	node->pid = pid;
	return (0);
}

/*
** Handles the execution of commands in the middle of a pipeline.
** Handles input/output redirection and executes the command.
*/
int	ft_pipe_middle(t_cmd *node, int pipe_fd[2], int old_pipe_in, t_env *env_list)
{
	int	pid;

	pid = 0;
	if (node->fd_in != -1)
		dup2(node->fd_in, STDIN_FILENO);
	else
	{
		// write (2, "MIDDLE PIPE: dupping IN pipe\n", 30);
		dup2(old_pipe_in, STDIN_FILENO);
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		// write (2, "MIDDLE PIPE: dupping OUT pipe\n", 31);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	close(old_pipe_in);
	close(pipe_fd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (ft_is_builtin(node, env_list) == 0)
			exit (0);
		else if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
			exit (127);
	}
	node->pid = pid;
	return (0);
}

/*
** Handles the execution of the last command in a pipeline.
** Handles input/output redirection and executes the command.
*/
int	ft_pipe_last(t_cmd *node, int pipe_fd[2], int old_pipe_in, t_env *env_list)
{
	int	pid;

	pid = 0;
	if (node->fd_in != -1)
		dup2(node->fd_in, STDIN_FILENO);
	else
	{
		// write (2, "dupping IN last pipe\n", 22);
		dup2(old_pipe_in, STDIN_FILENO);
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (ft_is_builtin(node, env_list) == 0)
			exit (0);
		if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
			exit (127);
	}
	node->pid = pid;
	return (0);
}

/*
** Executes a sequence of commands, possibly connected by pipes.
** Determines the position of each command and executes it accordingly.
** 1. checks if its only one node, meaning a simple cmd
** 2. loop through nodes of linked list
** 3. checks if there is a next and prev node, meaning we are in middle
** 4. checks if we are in the first node
** 5. checks if we are in the last node
** 6. we save the old fd_in into old_pipe_in
** 7. move on to the next node in the linked list
*/

int	loop_cmds(t_cmd *node, int exit_status, t_cmd *head, t_env *env_list)
{
	int old_pipe_in = 0;
	int pipe_fd[2];
	int std_in = dup(STDIN_FILENO);
	int std_out = dup(STDOUT_FILENO);
	while(node)
	{
		if (node->next && node->prev)
		{
			// printf("entering middle pipe cmd is %s\n", node->cmd[0]);
			write(2, "\nentering middle pipe\n", 22);
			pipe(pipe_fd);
			ft_pipe_middle(node, pipe_fd, old_pipe_in, env_list);
		}
		else if(node->next)
		{
			// write(2, "\nentering first pipe\n", 21);
			pipe(pipe_fd);
			ft_pipe_first(node, pipe_fd, env_list);
			// printf("entering first pipe cmd is %s\n", node->cmd[0]);
		}
		else
		{
			// write(2, "\nentering last pipe\n", 21);
			ft_pipe_last(node, pipe_fd, old_pipe_in, env_list);
			// printf("entering last pipe, cmd is %s\n", node->cmd[0]);
		}
		old_pipe_in = pipe_fd[0];
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		node = node->next;
	}
	close_after(std_in, std_out, pipe_fd);
	exit_status = handle_exit_status(head);
	return(exit_status);
}

void	close_after(int std_in, int std_out, int pipe_fd[2])
{
	if (std_in >= 0)
		close(std_in);
	if (std_out >= 0)
		close(std_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	ft_executor(t_cmd *node, t_env *env_list)
{
	int		exit_status;
	t_cmd	*head;
	// char	**env1;
	int		pid;

	exit_status = 0;
	head = node;
	pid = 0;
	// env1 = NULL;
	// env1 = ft_env_list_to_array(node->m_env);
	// env1 = ft_env_list_to_array(env_list);
	ft_init_signals_input();
	if (!node->next && !node->prev)
		exit_status = ft_simple_cmd(node, exit_status, pid, env_list);
	else
	{
		exit_status = loop_cmds(node, exit_status, head, env_list);
	}

	// free environment here
	// free cmd struct
	// free_env(env1);
	//seg faults for heredoc
	ft_free_cmd_struct(node);
	return (exit_status);
}
