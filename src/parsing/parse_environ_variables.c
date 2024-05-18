/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:55:51 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/18 19:47:07 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//function iterates through environment struct looking for a match
//when match is found, it copies everything after the '=' on from 
//environment
char	*find_substitution(t_env *env, char *name)
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