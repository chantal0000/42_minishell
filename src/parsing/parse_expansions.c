/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:42:49 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 10:38:30 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
checks the command arrays in linked lists for expansions
*/
void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int *exit_status)
{
	t_cmd	*temp;
	int		i;

	if (!cmd || !*cmd || !env || !exit_status)
		return ;
	temp = *cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			expand_exit_status(&temp->cmd[i], exit_status);
			expand_variables(&temp->cmd[i], env);
			i++;
		}
		temp = temp->next;
	}
}

/*
Update the input string with the variable value
-if string empty and var_value not empty, copy var_value
-if string & var_value empty, copy ""
-else copy string
*/
void	update_string(char **s, char *var_value, char *second_s)
{
	char	*beg_part;
	char	*new;

	if (!*s[0] && var_value)
	{
		beg_part = ft_strdup(var_value);
		new = ft_strjoin(beg_part, second_s);
	}
	else if (!*s[0] && !var_value)
	{
		beg_part = ft_strdup("");
		new = ft_strjoin(beg_part, second_s);
	}
	else
	{
		beg_part = ft_strdup(*s);
		new = ft_strjoin(beg_part, var_value);
		new = ft_strjoin(new, second_s);
	}
	free(*s);
	free(beg_part);
	*s = new;
}

/*
Finds variable in env, if var is found, proceeds
to substitute value of var, checking for valid characters
& updates the string
*/
void	expand_variables(char **s, t_env *env)
{
	char	*position;
	char	*name;
	char	*value;
	int		len;

	position = find_var_position(*s);
	while (position != NULL)
	{
		*position = '\0';
		len = 0;
		while (position[len + 1] && (valid_name(&position[len + 1])))
			len++;
		name = ft_strndup(position + 1, len);
		value = find_substitution(name, env);
		if (value)
		{
			update_string(s, value, position + 1 + len);
			free(name);
		}
		else
			value = ft_strdup("");
		position = find_var_position(*s);
	}
}

/*
finds the $ in string adn null terminates after $.
This splits the string to before $ and after.
First copies string before $, second jumps past $ &
copies rest
*/
void	expand_exit_status(char **s, int *exit_status)
{
	char	*exp_pos;
	char	*first;
	char	*second;
	char	*expansion;
	char	*temp;

	exp_pos = ft_strstr(*s, "$?");
	if (exp_pos)
	{
		*exp_pos = '\0';
		first = ft_strdup(*s);
		second = ft_strdup(exp_pos + 2);
		expansion = ft_itoa(*exit_status);
		temp = expanded_string(first, expansion, second);
		free(first);
		free(second);
		free(expansion);
		free(*s);
		*s = temp;
	}
}

char	*expanded_string(char *first, char *expansion, char *second)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(first) + ft_strlen(expansion) + ft_strlen(second);
	temp = ft_calloc((len + 1), sizeof(char));
	if (temp)
	{
		ft_strcpy(temp, first);
		ft_strcat(temp, expansion);
		ft_strcat(temp, second);
	}
	return (temp);
}
