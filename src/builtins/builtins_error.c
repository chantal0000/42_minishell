/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:00:24 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/18 15:12:29 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** ERROR IN EXPORT
*/
int	ft_handle_error_export(t_cmd *cmd)
{
	int i = 0;
	write(STDERR_FILENO, "minishell: ", 12);
	while(cmd->cmd[i])
	{
		write(STDERR_FILENO, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		write(STDERR_FILENO, ": ", 2);
		i++;
	}
		write(STDERR_FILENO, "not a valid identifier", 25);
		write(STDERR_FILENO, "\n", 1);
		// FREE?
	return (1);
}

int	ft_handle_error_cd(t_cmd *cmd)
{
	int i = 0;
	write(STDERR_FILENO, "minishell: ", 12);
	while(cmd->cmd[i])
	{
		write(STDERR_FILENO, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		write(STDERR_FILENO, ": ", 2);
		i++;
	}
		write(STDERR_FILENO, "No such file or directory", 26);
		write(STDERR_FILENO, "\n", 1);
		// FREE?
	return (1);
}
