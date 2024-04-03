/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:32:24 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/03 17:39:14 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	char *cmd_to_check = cmd->cmd[0];
	// char *cmd_to_check = "export hallo";

	if (ft_strncmp(cmd_to_check, "exit", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: exit\n");
	else if (ft_strncmp(cmd_to_check, "cd", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: cd\n");
	else if (ft_strncmp(cmd_to_check, "echo", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: echo\n");
	else if (ft_strncmp(cmd_to_check, "env", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: env\n");
	else if (ft_strncmp(cmd_to_check, "export", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: export\n");
	else if (ft_strncmp(cmd_to_check, "pwd", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: pwd\n");
	else if (ft_strncmp(cmd_to_check, "unset", ft_strlen(cmd_to_check)) == 0)
		printf("built-in: unset\n");
	else
	{
		printf("not a built-in\nreturn with -1 \n");
		return (-1);
	}
	return (0);
}
