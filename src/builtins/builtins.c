/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:32:24 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/13 15:51:21 by chbuerge         ###   ########.fr       */
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

int	ft_is_builtin(t_cmd *cmd, t_env **env_list, int original_stdin, int original_stdout)
{
	char	*cmd_to_check;
	int		exit_status;

	exit_status = 0;
	cmd_to_check = cmd->cmd[0];
	if (ft_strcmp(cmd_to_check, "exit") == 0)
		exit_status = ft_exit(cmd, env_list, original_stdin, original_stdout);
	else if (ft_strcmp(cmd_to_check, "cd") == 0)
		exit_status = ft_cd(cmd);
	else if (ft_strcmp(cmd_to_check, "echo") == 0)
		exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd_to_check, "env") == 0)
		exit_status = ft_env(cmd, env_list);
	else if (ft_strcmp(cmd_to_check, "export") == 0)
		exit_status = ft_export(cmd, env_list);
	else if (ft_strcmp(cmd_to_check, "pwd") == 0)
		exit_status = ft_pwd();
	else if (ft_strcmp(cmd_to_check, "unset") == 0)
		exit_status = ft_unset(cmd, env_list);
	else
		return (-1);
	return (exit_status);
}
