/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:35:02 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/10 12:35:56 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** env command in Unix-like operating systems prints a list of environment
** variables and their values
*/

int	ft_env(t_cmd *cmd, t_env *env_list)
{
	t_env	*current;

	if(cmd->cmd[1] != NULL)
	{
		if (ft_handle_error_cd(cmd) == 1)
			return (1);
	}
	current = env_list;
	while (current)
	{
		printf("%s\n", current->cmd_env);
		current = current->next;
	}
	return (0);
}
