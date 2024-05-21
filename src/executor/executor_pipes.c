/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:17:22 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/21 15:10:45 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit_free(t_minishell *minishell_struct, t_cmd *node, int exit_status)
{
	ft_free_cmd_struct(first_node(node));
	ft_free_env_list(&(minishell_struct->env_list));
	close(minishell_struct->og_stdin);
	close(minishell_struct->og_stdout);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free(minishell_struct);
	exit (exit_status);
}

/*
** Handles the execution of the first command in a pipeline.
** Handles input/output redirection and executes the command.
** - 1 meaning there if no in/out file
** 1. if there is an infile we dup the files fd for stdin
** 2. if there is an outfile we dup the files fd for stdout
** 3. else we set the stdout to pipe_fd[1] (write end)
*/
int	ft_pipe_first(t_cmd *node, int pipe_fd[2], t_minishell *minishell_struct)
{
	int	exit_status;

	exit_status = 0;
	ft_set_pipes_first(node, pipe_fd);
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, minishell_struct);
		if (exit_status == -1)
			exit_status = execute_cmd
				(ft_env_list_to_array(minishell_struct->env_list), node->cmd);
		ft_exit_free(minishell_struct, node, exit_status);
	}
	return (0);
}

/*
** Handles the execution of commands in the middle of a pipeline.
** Handles input/output redirection and executes the command.
*/
int	ft_pipe_middle(t_cmd *node, int pipe_fd[2],
	int old_p_in, t_minishell *minishell_struct)
{
	int	exit_status;

	exit_status = 0;
	ft_set_pipe_middle(node, pipe_fd, old_p_in);
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, minishell_struct);
		if (exit_status == -1)
			exit_status = execute_cmd
				(ft_env_list_to_array(minishell_struct->env_list), node->cmd);
		ft_exit_free(minishell_struct, node, exit_status);
	}
	return (0);
}

/*
** Handles the execution of the last command in a pipeline.
** Handles input/output redirection and executes the command.
*/
int	ft_pipe_last(t_cmd *node, int pipe_fd[2],
	int old_p_in, t_minishell *minishell_struct)
{
	int	exit_status;

	exit_status = 0;
	ft_set_pipe_last(node, pipe_fd, old_p_in);
	node->pid = fork();
	if (node->pid == 0)
	{
		close(pipe_fd[0]);
		exit_status = ft_is_builtin(node, minishell_struct);
		if (exit_status == -1)
			exit_status = execute_cmd
				(ft_env_list_to_array(minishell_struct->env_list), node->cmd);
		ft_exit_free(minishell_struct, node, exit_status);
	}
	return (0);
}
