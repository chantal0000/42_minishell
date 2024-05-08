/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:40:13 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/08 12:06:37 by chbuerge         ###   ########.fr       */
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

int	ft_unset(t_cmd *cmd, t_env *env_list)
{
	t_env	*temp;
	t_env	*prev;

	if (!env_list)
		return (1);
	temp = env_list;
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->cmd_env, cmd->cmd[1], ft_len_until_delimiter(temp->cmd_env)) == 0)
		{
			if (prev == NULL)
			{
				// temp = temp->next;
				// temp->next = temp->next->next;
				// free(temp);
				free(env_list->cmd_env);
				env_list = temp->next;
    			// free(temp); // Free the original head node
				return (0);
			}
			else
			{
				prev->next = temp->next;
				free(temp);
			}
				// env_list = temp;
				return (0);
		}

		prev = temp;
		temp = temp->next;
	}

	return (0);

}
