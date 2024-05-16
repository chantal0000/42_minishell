/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/16 17:30:08 by kbolon           ###   ########.fr       */
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
				split_on_dollar(&temp->cmd[i], env, exit_status);
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
	int		i;

	i = 0;
	new_str = NULL;
	if (**s == '$')
	{
		temp = find_and_substitute(*s, env, exit_status);
		if (temp)
			*s = temp;
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
				free_memory(arr);
				return ;
			}
			else
				new_str = make_new_str(arr, new_str, temp);
			free(temp);
			i++;
		}
		*s = new_str;
		free(new_str);
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
	{
		free_memory(arr);
		return (NULL);
	}
	if (new_str == NULL)
	{
		new_str = ft_strjoin(arr[i], temp);
		if (!new_str)
		{
			free_memory(arr);
			free (temp);
			return (NULL);
		}
	}
	return (new_str);
}

char	*make_new_str(char **arr, char *new_str, char *temp)
{
	new_str = ft_strjoin(new_str, temp);
	if (!new_str)
	{
		free_memory(arr);
		free(new_str);
		free (temp);
		return (NULL);
	}
	return (new_str);
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
/*char *extract_variable_name(char *s) {
    char *start = s;
    if (!s || (*s != '_' && !isalpha(*s))) {
        return NULL;  // Not a valid start for a variable name
    }

    while (*s && (isalnum(*s) || *s == '_')) {
        s++;
    }

    // Allocate a new string for the variable name
    int len = s - start;
    char *var_name = (char *)malloc(len + 1);
    if (var_name) {
        strncpy(var_name, start, len);
        var_name[len] = '\0';
    }
    return var_name;
}*/