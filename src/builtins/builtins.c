/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:32:24 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/22 17:15:57 by kbolon           ###   ########.fr       */
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

int	ft_is_builtin(t_cmd *cmd, t_env *env_list)
{
	char *cmd_to_check;

	cmd_to_check = cmd->cmd[0];
	// printf("cmd_to_check: %s\n", cmd_to_check);

	if (ft_strcmp(cmd_to_check, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd_to_check, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd_to_check, "echo") == 0)
	{
		ft_echo(cmd);
//		printf("built-in: echo\n");
	}
	else if (ft_strcmp(cmd_to_check, "env") == 0)
		ft_env(env_list);
	else if (ft_strcmp(cmd_to_check, "export") == 0)
	{
		ft_export(cmd, env_list);
	}
	else if (ft_strcmp(cmd_to_check, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd_to_check, "unset") == 0)
		ft_unset(cmd, env_list);
	else
	{
		// printf("not a built-in\nreturn with -1 \n");
		return (-1);
	}
	return (0);
}
