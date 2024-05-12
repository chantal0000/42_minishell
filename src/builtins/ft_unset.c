/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:40:13 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/12 15:30:45 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** removes the var in environment that is defined as argument,
** if no arg no effect
*/

int	ft_len_until_delimiter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '='))
		i++;
	return i;
}

int	ft_unset(t_cmd *cmd, t_env **env_list)
{
	t_env	*current;
	t_env	*prev = NULL;

	if (!env_list)
		return (0);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->cmd_env, cmd->cmd[1], ft_len_until_delimiter(current->cmd_env)) == 0)
		{
			if (prev == NULL)
			{
				*env_list = current->next;
  				free(current->cmd_env);
				free(current);
				return (0);
			}
			else
			{
				prev->next = current->next;
				free(current->cmd_env);
				free(current);
				return (0);
			}
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
