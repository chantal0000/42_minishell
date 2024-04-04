/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/04 16:24:00 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd *tree)
{
	t_cmd	*temp;

	if (!tree)
		return ;
	while (tree)
	{
		temp = tree;
		if (temp->fd_in >= 0)
			close(temp->fd_in);
		if (temp->fd_out >= 0)
			close(temp->fd_out);
		if (temp->m_env)
			free_env(temp->m_env);
		free(temp->file_name);
		tree = tree->next;
		free(temp);
	}
	free(tree);
}

void	free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_env(t_env	*env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = temp->next;
		free(temp);
	}
	free(env);
}
