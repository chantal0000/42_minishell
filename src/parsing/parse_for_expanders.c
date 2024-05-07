/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expanders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:55:51 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/07 06:41:45 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_var_name(char *s, t_exp *exp)
{
	char	*var_exp;
	size_t		cmd_len;
	char	*result;

	if (!s)
		return (NULL);
	var_exp = NULL;
	cmd_len = 0;
	if (*s == '$')
		s = check_for_question_mark(s);
	while (s[cmd_len] != '\0' && !is_token(s[cmd_len]) && !is_whitespace(s[cmd_len]))
		cmd_len++;
	var_exp = parse_for_duplicate_names(exp, s, cmd_len);
	if (var_exp == NULL)
		return (ft_strdup(""));
	result = ft_strjoin(var_exp, s + cmd_len);
	free (var_exp);
	if (!result)
		return (NULL);
	return (result);
}

char	*parse_for_duplicate_names(t_exp *exp, char *s, size_t cmd_len)
{
	size_t	var_len;
	t_exp	*temp;
	char	*var_exp;

	var_len = 0;
	var_exp = NULL;
	temp = exp;
	while (temp)
	{
		var_len = ft_strlen(temp->exp_name);
		if (ft_strncmp(s, temp->exp_name, var_len) == 0 && var_len == cmd_len)
		{
			if (temp->exp_value != NULL)
			{
				var_exp = ft_strdup(temp->exp_value);
				if (!var_exp)
					return (NULL);
			}
			break ;
		}
		temp = temp->next;
	}
	return (var_exp);
}

char	*check_for_question_mark(char *s)
{
	char	*temp;

	temp = s;
	if (*temp == '$')
	{
		temp++;
		if (*temp == '?')
		{
			printf("question mark found\n");
			temp++;
		}
		temp++;
		s = temp;
	}
	return (s);
}

char	*parse_string_for_expansions(char *s, t_exp *exp)
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
			temp = ft_var_name(temp, exp);
			if (!temp)
				return (NULL);
			str = ft_strndup(s, i);
			if (!str)
				return (free(temp), NULL);
			new_str = ft_strjoin(str, temp);
			return (free(temp), free(str), new_str);
		}
		i++;
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
			string = ft_var_name(temp->cmd[i], exp);
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
