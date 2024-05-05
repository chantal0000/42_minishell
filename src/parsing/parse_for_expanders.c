/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:55:51 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/05 20:19:54 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_var_name2(char *s, t_exp *exp)
{
	char	*var_exp;
	int		var_len;
	t_exp	*temp;
	int 	cmd_len;
//	char	*str_temp;
	char	*result;

	var_exp = NULL;
	cmd_len = 0;
	var_len = 0;
	if (*s == '$')
		s++;
	while (s[cmd_len] != '\0' && !is_whitespace(s[cmd_len]))
		cmd_len++;
	temp = exp;
	while (temp)
	{
		var_len = strlen(temp->exp_name);
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

char	*parse_string_for_expansions(char *s, t_exp *exp)
{
	char	*temp;
	char	*str;
	int		i;
	int		len;
	char 	*new_str;

	str = s;
	i = 0;
	len = 0;
	new_str = NULL;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		temp = &str[i];
		temp = ft_var_name2(temp, exp);
		if (!temp)
			return (NULL);
		len = strlen(temp);
		str = strndup(s, i);
		if (!str)
		{
			free (temp);
			return (NULL);
		}
		new_str = ft_strjoin(str, temp);
		free (temp);
		free (str);
		return (new_str);
	}
	return (s);
}


void	parse_cmds_for_expansions(t_cmd **cmd, t_exp *exp)
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
			string = ft_var_name2(temp->cmd[i], exp);
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
