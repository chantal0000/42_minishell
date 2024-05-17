/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:40:13 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 16:18:15 by chbuerge         ###   ########.fr       */
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
	return (i);
}

/*
** compares the recieved arguments with the environmental list to see if it
** finds a value to unset
*/
int	find_match(t_env *current, char *str)
{
	if (ft_strncmp(current->cmd_env, str,
			ft_len_until_delimiter(current->cmd_env)) == 0)
		return (0);
	else
		return (1);
}

void	handle_unset(t_env *current, t_env *prev, t_env **env_list)
{
	if (prev == NULL)
		*env_list = current->next;
	else
		prev->next = current->next;
	free(current->cmd_env);
	free(current);
}

int	ft_unset(t_cmd *cmd, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	if (!env_list)
		return (0);
	current = *env_list;
	while (cmd->cmd[i])
	{
		prev = NULL;
		current = *env_list;
		while (current)
		{
			if (find_match(current, cmd->cmd[i]) == 0)
			{
				handle_unset(current, prev, env_list);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
