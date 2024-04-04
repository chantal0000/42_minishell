/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:32:24 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/04 11:12:39 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	char *cmd_to_check;

	cmd_to_check = cmd->cmd[0];
	printf("cmd_to_check: %s\n", cmd_to_check);

	if (ft_strncmp(cmd_to_check, "exit", 4) == 0)
		printf("built-in: exit\n");
	else if (ft_strncmp(cmd_to_check, "cd", 2) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd_to_check, "echo", 4) == 0)
		printf("built-in: echo\n");
	else if (ft_strncmp(cmd_to_check, "env", 3) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd_to_check, "export", 6) == 0)
		printf("built-in: export\n");
	else if (ft_strncmp(cmd_to_check, "pwd", 3) == 0)
		printf("built-in: pwd\n");
	else if (ft_strncmp(cmd_to_check, "unset", 5) == 0)
		printf("built-in: unset\n");
	else
	{
		printf("not a built-in\nreturn with -1 \n");
		return (-1);
	}
	return (0);
}
