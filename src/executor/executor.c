/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:35:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 18:43:23 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_exit_simple_cmd(t_cmd *node, int exit_status)
{
	waitpid(node->pid, &exit_status, WUNTRACED);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else
		exit_status = 130;
	return (exit_status);
}

/*
** Executes a simple command. If it's a built-in command, it's executed directly.
** Otherwise, it handles redirections and executes using execve().
	// WIFEEXITED is 0, when CTRL C
*/
int	ft_simple_cmd(t_cmd *node, int exit_status, t_minishell *minishell_struct)
{
	if ((node->fd_in) != -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	exit_status = ft_is_builtin(node, minishell_struct);
	if (exit_status != -1)
		return (exit_status);
	else
	{
		node->pid = fork();
		if (node->pid == 0)
		{
			exit_status = execute_cmd
				(ft_env_list_to_array(minishell_struct->env_list), node->cmd);
			ft_exit_free(minishell_struct, node, exit_status);
		}
		else
			return (handle_exit_simple_cmd(node, exit_status));
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

int	loop_cmds(t_cmd *node, t_cmd *head, t_minishell *minishell_struct)
{
	int	old_p_in;
	int	pipe_fd[2];

	old_p_in = 0;
	while (node)
	{
		if (node->next)
			pipe(pipe_fd);
		if (!node->prev && node->next)
			ft_pipe_first(node, pipe_fd, minishell_struct);
		else if (node->prev && node->next)
			ft_pipe_middle(node, pipe_fd, old_p_in, minishell_struct);
		else
			ft_pipe_last(node, pipe_fd, old_p_in, minishell_struct);
		old_p_in = pipe_fd[0];
		ft_reset_std(minishell_struct->og_stdin, minishell_struct->og_stdout);
		node = node->next;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
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
int	ft_executor(t_cmd *node, t_minishell *minishell_struct)
{
	int		exit_status;
	t_cmd	*head;

	exit_status = 0;
	head = node;
	ft_init_signals_input();
	if (!node->next && !node->prev)
		exit_status = ft_simple_cmd(node, exit_status, minishell_struct);
	else
		exit_status = loop_cmds(node, head, minishell_struct);
	ft_free_cmd_struct(node);
	return (exit_status);
}
