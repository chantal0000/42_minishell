/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:16:16 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/13 10:06:00 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** export with no options
** sets environment variables
** if used without arguments it prints all env variables
// bash: export: `var@=hello': not a valid identifier
*/

/*
** checks that there is at least one equal sign otherwise returns 1 to show err
*/
int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[0] != '_') && (ft_isalpha(str[0]) != 1))
		{
			printf("%s: not a valid identifier\n", str);
			return (1);
		}
		if ((str[i] != '_') && (ft_isalnum(str[i]) != 1))
		{
			printf("%s: not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	if (check_for_equal(str) == 1)
		return (1);
	return (0);
}

int	ft_export(t_cmd *cmd, t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	if (cmd->cmd[1] == NULL)
	{
		while ((temp != NULL) && (temp->cmd_env != NULL))
		{
			printf("declare -x ");
			printf("%s\n", temp->cmd_env);
			temp = temp->next;
		}
		return (0);
	}
	if (ft_check_syntax(cmd->cmd[1]) == 0)
	{
		ft_unset(cmd, env_list);
		insert_end(env_list, cmd->cmd[1]);
		return (0);
	}
	return (1);
}
