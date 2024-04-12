/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:32:24 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/12 16:51:45 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_is_builtin(t_cmd *cmd)
{
	char *cmd_to_check;

	cmd_to_check = cmd->cmd[0];
	// printf("cmd_to_check: %s\n", cmd_to_check);

	if (ft_strcmp(cmd_to_check, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd_to_check, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd_to_check, "echo") == 0)
		printf("built-in: echo\n");
	else if (ft_strcmp(cmd_to_check, "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd_to_check, "export") == 0)
	{
		ft_export(cmd);
	}
	else if (ft_strcmp(cmd_to_check, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd_to_check, "unset") == 0)
		printf("built-in: unset\n");
	else
	{
		// printf("not a built-in\nreturn with -1 \n");
		return (-1);
	}
	return (0);
}
