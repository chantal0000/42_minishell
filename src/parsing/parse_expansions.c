/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/12 16:24:16 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int *exit_status)
{
	t_cmd	*temp;
	int		i;
	char	*string;

	if (!cmd || !*cmd)
		return ;
	temp = *cmd;
	string = NULL;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			if (find_dollar_sign(temp->cmd[i]))
				temp->cmd[i] = split_on_dollar(temp->cmd[i], env, exit_status);
			i++;
		}
		temp = temp->next;
	}
}

char	*split_on_dollar(char *s, t_env *env, int *exit_status)
{
	char	**arr;
	char	*string;
	char	*temp;

	string = s;
	temp = NULL;
	if (*s == '$')
		string = find_and_substitute(s, env, exit_status);
	else
	{
		arr = ft_split(s, '$');
		if (!arr)
			return (NULL);
		string = find_and_substitute(arr[1], env, exit_status);
		if (!string)
			error_memory(arr, NULL);
		temp = ft_strjoin(arr[0], string);
		if (!temp)
			error_memory(arr, string);
		free (string);
		free_array(arr);
		return (temp);
	}
	return (string);
}

char	*find_and_substitute(char *s, t_env *env, int *exit_status)
{
	char	*string;
	char	*temp;

	temp = s;
	temp = move_past_dollar(temp);
	string = ft_variable(temp, env, exit_status);
	if (string && *string != '\0')
	{
		free (temp);
		temp = string;
	}
	else
		free (string);
	return (temp);
}

void	free_array(char **arr)
{
	size_t	i;

	i = 0;
	if (!*arr || !arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
