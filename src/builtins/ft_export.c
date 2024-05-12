/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:16:16 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/12 15:31:36 by chbuerge         ###   ########.fr       */
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
// bash: export: `var@=hello': not a valid identifier

int	ft_check_syntax(char *str)
{
	int	i;
	int	flag_equal = 0;

	i = 0;
	while(str[i] && str[i] != '=')
	{
		if (str[0] != '_' && (ft_isalpha(str[0]) != 1))
		{
			printf("str[0] is %c return -1\n", str[0]);
			return (1);
		}
		if(str[i] != '_' && (ft_isalnum(str[i]) != 1))
		{
			printf("before '=' %c\n", str[i]);
			return (1);
		}
		i++;
	}
	while (str[i])
	{
		if (str[i] == '=')
			flag_equal = 1;
		i++;
	}
		i++;
	if (flag_equal != 1)
		return (1);
	return (0);
}
int	ft_export(t_cmd *cmd, t_env **env_list)
{
	t_env *temp = *env_list;
	if (cmd->cmd[1] == NULL)
	{
		while ((temp != NULL) && (temp->cmd_env != NULL))
		{
			printf("declare -x ");
			printf("%s\n", temp->cmd_env);
			temp = temp->next;
		}
		return (0);
	}
	if (ft_check_syntax(cmd->cmd[1]) == 0)
	{
		ft_unset(cmd, env_list);
		insert_end(env_list, cmd->cmd[1]);
		return (0);
	}
	return (1);

}
