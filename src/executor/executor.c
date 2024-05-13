/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:35:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/13 16:35:17 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Executes a simple command. If it's a built-in command, it's executed directly.
** Otherwise, it handles redirections and executes using execve().
*/
int	ft_simple_cmd(t_cmd *node, int exit_status, t_env **env_list)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if ((node->fd_in) != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		// added does this break my stuff
		// close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	// pass stdin stdout here
	exit_status = ft_is_builtin(node, env_list, original_stdin, original_stdout);
	if (exit_status != -1)
	{
		if (original_stdin > 3)
			close(original_stdin);
		if(original_stdin > 3)
			close(original_stdout);
		return (exit_status);
	}
	else
	{
		node->pid = fork();
		if (node->pid == 0)
			ft_start_exec(*env_list, node);
		else
		{
			waitpid(node->pid, &exit_status, WUNTRACED);
			exit_status = WEXITSTATUS(exit_status);
			dup2(original_stdin, STDIN_FILENO);
			close(original_stdin);
			dup2(original_stdout, STDOUT_FILENO);
			close(original_stdout);
			return (exit_status);
		}
	}
	return (exit_status);
}

/*
** Executes a sequence of commands, possibly connected by pipes.
** Determines the position of each command and executes it accordingly.
** 1. checks if its only one node, meaning a simple cmd
** 2. loop through nodes of linked list
** 3. checks if there is a next and prev node, meaning we are in middle
** 4. checks if we are in the first node
** 5. checks if we are in the last node
** 6. we save the old fd_in into old_p_in
** 7. move on to the next node in the linked list
*/

int	loop_cmds(t_cmd *node, t_cmd *head, t_env **env_list)
{
	int	old_p_in;
	int	pipe_fd[2];
	int	std_in;
	int	std_out;

	old_p_in = 0;
	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	while (node)
	{
		if (node->next)
			pipe(pipe_fd);
		if (!node->prev && node->next)
			ft_pipe_first(node, pipe_fd, *env_list);
		else if (node->prev && node->next)
			ft_pipe_middle(node, pipe_fd, old_p_in, *env_list);
		else
			ft_pipe_last(node, pipe_fd, old_p_in, *env_list);
		old_p_in = pipe_fd[0];
		ft_reset_std(std_in, std_out);
		node = node->next;
	}
	close_after(std_in, std_out, pipe_fd);
	return (handle_exit_status(head));
}

/*
** BEGINNING OF EXECUTION
** inits signals (second time)
** checks if we have just one single command and proceeds
** or if we have multiple goes to the loop of commands
** if successful we free the linked list -> cmd structure
** and return the exit status to our main function
*/
int	ft_executor(t_cmd *node, t_env **env_list)
{
	int		exit_status;
	t_cmd	*head;

	exit_status = 0;
	head = node;
	ft_init_signals_input();
	if (!node->next && !node->prev)
		exit_status = ft_simple_cmd(node, exit_status, env_list);
	else
		exit_status = loop_cmds(node, head, env_list);
	ft_free_cmd_struct(node);
	return (exit_status);
}
