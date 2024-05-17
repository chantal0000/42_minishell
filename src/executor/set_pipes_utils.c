/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:52 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 12:43:44 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_set_pipes_first(t_cmd *node, int pipe_fd[2])
{
	if ((node->fd_in) != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
		close(pipe_fd[1]);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
}

void	ft_set_pipe_middle(t_cmd *node, int pipe_fd[2], int old_p_in)
{
	if (node->fd_in != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	else
		dup2(old_p_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
		close(pipe_fd[1]);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(old_p_in);
	close(pipe_fd[1]);
}

void	ft_set_pipe_last(t_cmd *node, int pipe_fd[2], int old_p_in)
{
	if (node->fd_in != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	else
		dup2(old_p_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
		close(pipe_fd[1]);
	}
	close(pipe_fd[1]);
}
