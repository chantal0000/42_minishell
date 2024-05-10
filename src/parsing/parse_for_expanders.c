/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:55:51 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/09 06:18:53 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_var_name2(char *s, t_exp *exp, int exit_status)
{
	char	*var_exp;
	int		var_len;
	t_exp	*temp;
	int		cmd_len;
	char	*result;

	var_exp = NULL;
	cmd_len = 0;
	var_len = 0;
	if (*s == '$')
	{
		if (*(s + 1) == '?')
		{
			result = ft_strdup(ft_itoa(exit_status));
			return (result);
		}
		s++;
	}
	while (ft_isalnum(s[cmd_len])) // Check if the character is alphanumeric
		cmd_len++;
	temp = exp;
	while (temp)
	{
		var_len = ft_strlen(temp->exp_name);
		if (ft_strncmp(s, temp->exp_name, var_len) == 0 && var_len == cmd_len)
		{
			if (temp->exp_value != NULL)
				var_exp = ft_strdup(temp->exp_value);
			break ;
		}
		temp = temp->next;
	}
	if (var_exp == NULL)
		return (ft_strdup(""));
	result = ft_strjoin(var_exp, s + cmd_len);
	if (!result)
		return (NULL);
	return (result);
}

char	*parse_string_for_expansions(char *s, t_exp *exp, int exit_status)
{
	char	*temp;
	char	*str;
	int		i;
	char	*new_str;

	str = s;
	i = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			temp = &str[i];
			temp = ft_var_name2(temp, exp, exit_status);
			if (!temp)
				return (NULL);
			str = ft_strndup(s, i);
			if (!str)
			{
				free(temp);
				return (NULL);
			}
			new_str = ft_strjoin(str, temp);
			free(temp);
			free(str);
			return (new_str);
		}
		i++;
	}
	return (s);
}


void	parse_cmds_for_expansions(t_cmd **cmd, t_exp *exp, int exit_status)
{
	t_cmd	*temp;
	int		i;
	char	*string;

	if (!cmd)
		return ;
	temp = *cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			string = ft_var_name2(temp->cmd[i], exp, exit_status);
			if (string && *string != '\0')
			{
				free (temp->cmd[i]);
				temp->cmd[i] = string;
			}
			else
				free (string);
			i++;
		}
		temp = temp->next;
	}
}
