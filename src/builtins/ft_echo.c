/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/16 12:09:41 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (cmd->cmd[i] == NULL)
		return (write(1, "\n", 1), 0);
	while (cmd->cmd[i] && !ft_strcmp(cmd->cmd[i], "-n"))
	{
		i++;
		new_line = 0;
	}
	if (!cmd->cmd[i])
	{
		if (!new_line)
			return (0);
		write(1, "\n", 1);
		return (0);
	}
	ft_write_echo(cmd->cmd, i);
	if (new_line)
		write(1, "\n", 1);
	return (0);
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	ft_write_echo(char **arr, int i)
{
	while (arr[i])
	{
		ft_putstr(arr[i]);
		if (arr[i + 1])
			write (1, " ", 1);
		i++;
	}
}
