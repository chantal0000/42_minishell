/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:55:51 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 10:31:37 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
checks for empty string & if char[0] is 
alpha numeric then check if rest of string is valid
(if alphanumeric/underscore, it returns 1)
*/
int	valid_name(char *s)
{
	if (!s || !ft_isalpha(*s))
		return (0);
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}

/*
Checks string for valid characters, finds the '$'
& checks next char is valid before it returns
a ptr to the '$' (if found)
*/
char	*find_var_position(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '$' && valid_name((s + 1)))
			return (s);
		s++;
	}
	return (NULL);
}

//function iterates through environment struct looking for a match
//when match is found, it copies everything after the '=' on from 
//environment
char	*find_substitution(char *name, t_env *env)
{
	t_env	*temp;
	size_t	len;
	char	*var;

	if (!env || !name)
		return (NULL);
	temp = env;
	len = ft_strlen(name);
	var = NULL;
	while (temp)
	{
		if (ft_strncmp(name, temp->cmd_env, len) == 0 && temp->cmd_env[len] == '=')
		{
			var = temp->cmd_env + len + 1;
			return (var);
		}
		temp = temp->next;
	}
	return (NULL);
}
