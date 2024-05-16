/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:55:51 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/16 12:29:15 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//this function iterates through the nodes searching for the 
//'=' sign and then returns the length of string before '='.
//this function iterates through the nodes searching for the 
//'=' sign and then returns the length of string before '='.
int	ft_find_environ_name(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=' && s[i] != '\n')
		i++;
	return (i);
}

//function looks for $, returns 1 if found
int	find_dollar_sign(t_cmd *cmd, char *s)
{
	t_cmd	*temp;

	temp = cmd;
	while (*s != '\0' && *s != '$')
		s++;
	if (*s == '$')
	{
		if (!ft_strcmp((s + 1), "?"))
			temp->token_env = '?';
		return (1);
	}
	return (0);
}

//function iterates through environment struct looking for a match
//when match is found, it copies everything after the '=' on from 
//environment
char	*find_substitution(t_env *env, char *s, size_t cmd_len)
{
	t_env	*temp;
	size_t	var_len;
	char	*var_exp;

	temp = env;
	var_exp = NULL;
	var_len = 0;
	while (temp)
	{
		var_len = ft_find_environ_name(temp->cmd_env);
		if (ft_strncmp(s, temp->cmd_env, cmd_len) == 0 && var_len == cmd_len)
		{
			var_exp = temp->cmd_env + var_len + 1;
			break ;
		}
		temp = temp->next;
	}
	return (var_exp);
}

//this function copies the environment into the command array 
//it copies everything beyond the '='
char	*ft_variable(char *s, t_env *env, int *exit_status)
{
	size_t	cmd_len;
	char	*result;
	char	*var_exp;

	var_exp = NULL;
	result = NULL;
	if (*(s) == '?')
		return (ft_itoa(*exit_status));
	cmd_len = ft_strlen(s);
	var_exp = find_substitution(env, s, cmd_len);
	if (var_exp == NULL)
		return (ft_strdup(""));
	result = ft_strjoin(var_exp, s + cmd_len);
	if (!result)
		return (NULL);
	s = result;
	free (result);
	return (s);
}

char	*move_past_dollar(char *s)
{
	char	*str;

	if (!s || *s != '$')
		return (s);
	str = s + 1;
	return (str);
}

