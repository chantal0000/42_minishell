/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:05:16 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 17:06:29 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_access(t_cmd *cmd)
{
	if (access(cmd->file_name, F_OK | W_OK) == -1)
	{
		perror("minishell: infile: No such file or directory");
		return (1);
	}
	return (0);
}

int	check_fd_in(t_cmd *cmd, int fd_in)
{
	if (fd_in && cmd->fd_in < 0)
	{
		if (check_access(cmd))
			return (1);
	}
	return (0);
}

int	check_fd_out(t_cmd *cmd, int fd_out)
{
	if (fd_out && cmd->fd_out < 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
		perror("Error Opening File");
		return (1);
	}
	if (check_access(cmd))
	{
		close (cmd->fd_out);
		cmd->fd_out = -1;
		return (1);
	}
	return (0);
}

int	check_access_and_fd(t_cmd *cmd, int fd_in, int fd_out)
{
	if (check_fd_in(cmd, fd_in))
		return (1);
	if (check_fd_out(cmd, fd_out))
		return (1);
	return (0);
}
