/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/14 18:28:11 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int *exit_status)
{
	t_cmd	*temp;
	int		i;

	if (!cmd || !*cmd)
		return ;
	temp = *cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			if (find_dollar_sign(temp->cmd[i]))
			{
				temp->token_env = 1;
				split_on_dollar(&temp->cmd[i], env, exit_status);
//				printf("temp->cmd[i]: %s\n", temp->cmd[i]);
			}
			i++;
		}
		temp = temp->next;
	}
}

void split_on_dollar(char **s, t_env *env, int *exit_status)
{
	char	**arr;
	char	*temp;
	char	*new_str;

	new_str = NULL;
	if (**s == '$')
	{
		temp = find_and_substitute(*s, env, exit_status);
		if (!temp)
			return ;
		*s = temp;
	}
	else
	{
		arr = ft_split(*s, '$');
		if (!arr)
			return ;
		temp = find_and_substitute(arr[1], env, exit_status);
		if (!temp)
		{
			free_array(arr);
			return ;
		}
		new_str = ft_strjoin(arr[0], temp);
		free(temp);
		free_array(arr);
		if (!new_str)
			return ;
		*s = new_str;
	}
}

char	*find_and_substitute(char *s, t_env *env, int *exit_status)
{
	char	*string;
	char	*temp;
	char	*temp1;

	temp = s;
	temp1 = move_past_dollar(temp);
	string = ft_variable(temp1, env, exit_status);
	if (string && *string != '\0')
		temp = string;
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
