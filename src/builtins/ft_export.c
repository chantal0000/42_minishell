/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:16:16 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 13:05:19 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** export with no options
** sets environment variables
** if used without arguments it prints all env variables
// bash: export: `var@=hello': not a valid identifier
*/
int	ft_unset_for_export(char *var_name, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list)
		return (0);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->cmd_env, var_name,
				ft_len_until_delimiter(current->cmd_env)) == 0)
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->cmd_env);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/*
** checks that there is at least one equal sign otherwise returns 1 to show err
*/
int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
// bash: export: `=moin': not a valid identifier

int	ft_check_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[0] != '_') && (ft_isalpha(str[0]) != 1))
		{
			printf("%s: not a valid identifier\n", str);
			return (1);
		}
		if ((str[i] != '_') && (ft_isalnum(str[i]) != 1))
		{
			printf("%s: not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	if (check_for_equal(str) == 1)
	{
		printf("%s: not a valid identifier\n", str);
		return (1);
	}
	return (0);
}

void	ft_export_print(t_env *temp)
{
	while ((temp != NULL) && (temp->cmd_env != NULL))
	{
		printf("declare -x %s\n", temp->cmd_env);
		temp = temp->next;
	}
}

int	ft_export(t_cmd *cmd, t_env **env_list)
{
	t_env	*temp;
	int		i;
	int		exit_status;

	i = 1;
	exit_status = 0;
	temp = *env_list;
	if (cmd->cmd[1] == NULL)
	{
		ft_export_print(temp);
		return (exit_status);
	}
	while (cmd->cmd[i] != NULL)
	{
		if (ft_check_syntax(cmd->cmd[i]) != 0)
			exit_status = 1;
		else
		{
			ft_unset_for_export(cmd->cmd[i], env_list);
			insert_end(env_list, cmd->cmd[i]);
		}
		i++;
	}
	return (exit_status);
}
