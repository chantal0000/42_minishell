/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/14 13:56:44 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_for_echo(t_cmd *cmd_tree)
{
	t_cmd	*temp;

	temp = cmd_tree;
	while (temp)
	{
		if (!ft_strcmp(temp->cmd[0], "echo") && !ft_strcmp(temp->cmd[1], "-n"))
			temp->token = 'n';
		else if (!ft_strcmp(temp->cmd[0], "echo") && \
			ft_strcmp(temp->cmd[1], "-n"))
			temp->token = 'e';
		else
			temp = temp->next;
	}
}

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
	t_cmd	*temp;
	int		num;
	int		i;

	if (!cmd)
		return (1);
	temp = cmd;
	check_echo_flags(temp);
	num = ft_count(temp->cmd);
	if (temp->token == 'n')
		i = 2;
	if (temp->token == 'e')
		i = 1;
	ft_write_echo(temp, num, i);
	if (cmd->token == 'e')
		ft_putchar_fd('\n', 1);
	return (0);
}

void	ft_write_echo(t_cmd *cmd, int num, int i)
{
	check_quotes(cmd->cmd[i]);
	if (i == num - 1 && cmd->cmd[i])
		ft_putstr_fd(cmd->cmd[i], 1);
	else
	{
		while (i < num)
		{
			if (i < num - 1 && cmd->cmd[i])
			{
				ft_putstr_fd(cmd->cmd[i], 1);
				ft_putchar_fd(' ', 1);
			}
			else
			{
				if (!cmd->cmd[1])
					ft_putchar_fd(' ', 1);
				ft_putstr_fd(cmd->cmd[i], 1);
			}
			i++;
		}
	}
}

void	check_echo_flags(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;
	int		j;
	int		count;

	temp = cmd;
	i = 2;
	j = 0;
	count = 0;
	while (temp)
	{
		count = ft_count(temp->cmd);
		if (count > 1)
		{
			if ((temp->cmd[0] && !ft_strcmp(temp->cmd[0], "echo")) && \
				(temp->cmd[1] && !ft_strcmp(temp->cmd[1], "-n")))
			{
				j = 0;
				while (temp->cmd[i] != NULL)
				{
					if (!ft_strcmp(temp->cmd[i], "-n"))
						j++;
					else
//						temp->cmd[i - j] = ft_strdup(temp->cmd[i]);
						temp->cmd[i - j] = temp->cmd[i];
					i++;
				}
				temp->cmd[i - j] = NULL;
			}
			temp = temp->next;
		}
	}
}
