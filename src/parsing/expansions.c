/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/10 17:43:08 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int exit_status)
{
	t_cmd	*temp;
	int		i;
	char	*string;

	if (!cmd)
		return ;
	temp = *cmd;
	string = NULL;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			if (find_dollar_sign(temp->cmd[i]))
			{
				temp->cmd[i] = move_past_dollar(temp->cmd[i]);
				string = ft_variable(temp->cmd[i], env, exit_status);
				if (string && *string != '\0')
				{
					free (temp->cmd[i]);
					temp->cmd[i] = string;
				}
				else
					free (string);
			}
			i++;
		}
		temp = temp->next;
	}
}
