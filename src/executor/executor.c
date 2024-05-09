/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:35:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/09 12:51:11 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Executes a simple command. If it's a built-in command, it's executed directly.
** Otherwise, it handles redirections and executes using execve().
*/

t_cmd *first_node(t_cmd *node)
{
	while (node->prev != NULL)
		node = node->prev;

	return (node);
}
int	ft_simple_cmd(t_cmd *node, int exit_status, int pid, t_env *env_list)
{
	if ((node->fd_in) != -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	exit_status = ft_is_builtin(node, env_list);
	if (exit_status != -1)
		return (exit_status);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
			{
				ft_free_env_list(env_list);
				ft_free_cmd_struct(node);
				exit (127);
			}
		}
		else
		{
			waitpid(pid, &exit_status, WUNTRACED);
			exit_status = WEXITSTATUS(exit_status);
			return (exit_status);
		}
	}
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
	int	exit_status;

	pid = 0;
	exit_status = 0;
	if ((node->fd_in) != -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, env_list);
		if (exit_status != -1)
			exit (exit_status);
		else if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
		{
			ft_free_env_list(env_list);
			ft_free_cmd_struct(node);
			exit (127);
		}
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
	int	exit_status;

	pid = 0;
	exit_status = 0;
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
		exit_status = ft_is_builtin(node, env_list);
		if (exit_status != -1)
			exit (exit_status);
		else if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
		{
			ft_free_env_list(env_list);
			ft_free_cmd_struct(first_node(node));
			exit (127);
		}
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
	int	exit_status;

	pid = 0;
	exit_status = 0;
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
		exit_status = ft_is_builtin(node, env_list);
		if (exit_status != -1)
			exit (exit_status);
		if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
		{
			ft_free_env_list(env_list);
			ft_free_cmd_struct(first_node(node));
			exit (127);
		}
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
// void ft_execute_pipeline_cmd(t_cmd *node, int *old_pipe_in, t_env *env_list)
// {
// 	int	pipe_fd[2];
// 	if (node->next && node->prev)
// 	{
// 		pipe(pipe_fd);
// 		ft_pipe_middle(node, pipe_fd, old_pipe_in, env_list);
// 	}
// 	else if (node->next)
// 	{
// 		pipe(pipe_fd);
// 		ft_pipe_first(node, pipe_fd, env_list);
// 	}
// 	else
// 		ft_pipe_last(node, pipe_fd, *old_pipe_in, env_list);
// 	*old_pipe_in = pipe_fd[0];
// }

void	ft_reset_std(int std_in, int std_out)
{
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
}

// int	loop_cmds(t_cmd *node, t_cmd *head, t_env *env_list)
// {
// 	int	old_pipe_in;
// 	int	pipe_fd[2];
// 	int	std_in;
// 	int	std_out;

// 	old_pipe_in = 0;
// 	std_in = dup(STDIN_FILENO);
// 	std_out = dup(STDOUT_FILENO);
// 	while (node)
// 	{
// 		if (node->next && node->prev)
// 		{
// 			pipe(pipe_fd);
// 			ft_pipe_middle(node, pipe_fd, old_pipe_in, env_list);
// 		}
// 		else if (node->next)
// 		{
// 			pipe(pipe_fd);
// 			ft_pipe_first(node, pipe_fd, env_list);
// 		}
// 		else
// 			ft_pipe_last(node, pipe_fd, old_pipe_in, env_list);
// 		old_pipe_in = pipe_fd[0];
// 		ft_reset_std(std_in, std_out);
// 		node = node->next;
// 	}
// 	close_after(std_in, std_out, pipe_fd);
// 	return (handle_exit_status(head));
// }

int	loop_cmds(t_cmd *node, t_cmd *head, t_env *env_list)
{
	int	old_pipe_in;
	int	pipe_fd[2];
	int	std_in;
	int	std_out;

	old_pipe_in = 0;
	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	while (node)
	{
		if (node->next)
			pipe(pipe_fd);
		if (!node->prev && node->next)
			ft_pipe_first(node, pipe_fd, env_list);
		else if (node->prev && node->next)
			ft_pipe_middle(node, pipe_fd, old_pipe_in, env_list);
		else
			ft_pipe_last(node, pipe_fd, old_pipe_in, env_list);
		old_pipe_in = pipe_fd[0];
		ft_reset_std(std_in, std_out);
		node = node->next;
	}
	close_after(std_in, std_out, pipe_fd);
	return (handle_exit_status(head));
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

/*
** beginning of execution
** inits signals (second time)
** checks if we have just one single command and proceeds
** or if we have multiple goes to the loop of commands
** if successful we free the linked list -> cmd structure
** and return the exit status to our main function
*/
int	ft_executor(t_cmd *node, t_env *env_list)
{
	int		exit_status;
	t_cmd	*head;
	int		pid;

	exit_status = 0;
	head = node;
	pid = 0;
	ft_init_signals_input();
	if (!node->next && !node->prev)
		exit_status = ft_simple_cmd(node, exit_status, pid, env_list);
	else
		exit_status = loop_cmds(node, head, env_list);
	ft_free_cmd_struct(node);
	return (exit_status);
}
