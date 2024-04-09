/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/09 17:16:24 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_cmdtree(t_cmd *tree)
{
	t_cmd	*temp;

	if (!tree)
		return ;
	while (tree)
	{
		temp = tree;
		if (temp->fd_in)
			close(temp->fd_in);
		if (temp->fd_out)
			close(temp->fd_out);
		if (temp->pid)
			close(temp->pid);
		if (temp->m_env)
			free_env(&temp->m_env);
		if (temp->file_name)
			free(temp->file_name);
		free_memory(temp->cmd);
		tree = tree->next;
	}
	free(temp);
	free(tree);
}

void	free_memory(char **arr)
{
	int	i;

	i = 0;
	if (!*arr || !arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env(t_env **env)
{
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free (env);
}
