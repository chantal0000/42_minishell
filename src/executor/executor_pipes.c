/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:17:22 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/09 14:50:37 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Handles the execution of the first command in a pipeline.
** Handles input/output redirection and executes the command.
** - 1 meaning there if no in/out file
** 1. if there is an infile we dup the files fd for stdin
** 2. if there is an outfile we dup the files fd for stdout
** 3. else we set the stdout to pipe_fd[1] (write end)
*/
int	ft_pipe_first(t_cmd *node, int pipe_fd[2], t_env *env_list)
{
	int	exit_status;

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
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, env_list);
		if (exit_status != -1)
			exit (exit_status);
		ft_start_exec(env_list, node);
	}
	return (0);
}

void	ft_pipe_set_pipes(t_cmd *node, int pipe_fd[2], int old_p_in)
{
	if (node->fd_in != -1)
		dup2(node->fd_in, STDIN_FILENO);
	else
		dup2(old_p_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(old_p_in);
	close(pipe_fd[1]);
}

/*
** Handles the execution of commands in the middle of a pipeline.
** Handles input/output redirection and executes the command.
*/
int	ft_pipe_middle(t_cmd *node, int pipe_fd[2], int old_p_in, t_env *env_list)
{
	int	exit_status;

	exit_status = 0;
	ft_pipe_set_pipes(node, pipe_fd, old_p_in);
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, env_list);
		if (exit_status != -1)
			exit (exit_status);
		ft_start_exec(env_list, node);
	}
	return (0);
}

/*
** Handles the execution of the last command in a pipeline.
** Handles input/output redirection and executes the command.
*/
int	ft_pipe_last(t_cmd *node, int pipe_fd[2], int old_p_in, t_env *env_list)
{
	int	exit_status;

	exit_status = 0;
	if (node->fd_in != -1)
		dup2(node->fd_in, STDIN_FILENO);
	else
		dup2(old_p_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[1]);
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, env_list);
		if (exit_status != -1)
			exit (exit_status);
		ft_start_exec(env_list, node);
	}
	return (0);
}
