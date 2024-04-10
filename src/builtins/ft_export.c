/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:16:16 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/10 19:44:09 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** export with no options
** sets environment variables
** if used without arguments it prints all env variables (env?)
** its possible to add multiple var to env

*/

// case1 no args, print env with declare -x
// case2 witha args
	//check if valid
	//check if it already exits?
		//if yes update
	//else create
// char	create_str(char *str)
// {

// }

int	ft_check_syntax(char *str)
{
	int	i;
	int	flag_equal = 0;

	i = 0;
	while(str[i])
	{
		if (str[0] != '_' && (ft_isalpha(str[0]) != 1))
		{
			printf("str[0] is %c return -1\n", str[0]);
			return (1);
		}
		else
			i++;
		while(str[i] && str[i] != '=')
		{
			if(str[i] != '_' && (ft_isalnum(str[i]) != 1))
			{
				printf("before '=' %c\n", str[i]);
				return (1);
			}
			i++;
		}
		if (str[i] == '=')
			flag_equal = 1;
		i++;
	}
	if (flag_equal != 1)
		return (1);
	printf("string: %s\n", str);
	// str[0] alpha or '_'
	// at least one '='
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	t_cmd *temp = cmd;
	printf("entering function ft_export\n");
	if (temp->cmd[1] == NULL)
	{
		while(temp->m_env)
		{
			printf("declare -x ");
			printf("%s\n", temp->m_env->cmd_env);
			temp->m_env = temp->m_env->next;
		}
	}
	else
	{
		printf("entering BEFORE check_syntax\n");
		//check syntax
		if (ft_check_syntax(cmd->cmd[1]) == 0)
		{
			printf("SUCCESS\n");
			// search if it exists in env and if yes reset
			// else add to env lst
		}
		else
			printf("FAIL\n");
	}
	return (0);
}
