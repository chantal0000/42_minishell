/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/17 17:07:40 by kbolon           ###   ########.fr       */
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
			if (find_dollar_sign(temp, temp->cmd[i]))
			{
				temp->token_env = '?';
				split_on_dollar(&temp->cmd[i], env, exit_status);
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
	char	*old_str;
	int		i;

	i = 0;
	new_str = NULL;
	if (**s == '$')
	{
		temp = find_and_substitute(*s, env, exit_status);
		if (temp)
		{
			free (*s);
			*s = temp;
		}
	}
	else
	{
		arr = ft_split(*s, '$');
		if (!arr)
			return ;
		while (arr[i] != NULL)
		{
			temp = ft_run_sub(&arr[i], env, exit_status);
			if (!temp)
			{
//				free_memory(arr);
				return ;
			}
			else
			{
				old_str = new_str;
				new_str = make_new_str(arr, new_str, temp);
				free(old_str);
				free(temp);
				free (*s);
				*s = new_str;
				free (new_str);
				free_memory(arr);
			}
			i++;
		}
/*		free (*s);
		*s = new_str;
		free (new_str);
		free_memory(arr);*/
	}
}

char	*ft_run_sub(char **arr, t_env *env, int *exit_status)
{
	char	*temp;
	char 	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	temp = find_and_substitute(arr[i + 1], env, exit_status);
	if (!temp)
		return (NULL);
	if (new_str == NULL)
	{
		new_str = ft_strjoin(arr[i], temp);
		if (!new_str)
		{
			free_memory(arr);
			return (NULL);
		}
		free(temp);
	}
	return (new_str);
}

char	*make_new_str(char **arr, char *new_str, char *temp)
{
	char	*result;

	result = ft_strjoin(new_str, temp);
	if (!result)
	{
		free_memory(arr);
		free(new_str);
		free (temp);
		return (NULL);
	}
	return (result);
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
		return (string);
//	else
//		free (string);
	return (s);
//	return (ft_strdup(temp));
}
