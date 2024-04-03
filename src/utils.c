/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/03 17:36:18 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmdtree(t_cmd *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return ;
	free_nodes(tree);
	if (tree->file_name)
		free(tree->file_name);
//	if (tree->m_env)
//		free_nodes(tree->m_env);
}

void	free_nodes(t_cmd *node)
{
	t_cmd	*temp;

	if (!node)
		return ;
	while (node)
	{
		temp = node;
		if (temp->fd_in)
			close(temp->fd_in);
		if (temp->fd_out)
			close(temp->fd_out);
		if (temp->m_env)
			free(temp->m_env->cmd_env);
		free(temp->file_name);
		node = node->next;
		free(temp);
	}
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
