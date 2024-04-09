/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/09 08:29:32 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_cmdtree(t_cmd *tree)
{
//	int	i;

//	i = 0;
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

/*void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		free_memory(cmd->cmd);
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		if (cmd->m_env)
			free_env(&cmd->m_env);
		free(cmd->file_name);
		cmd = cmd->next;
	}
	free (cmd);
}*/

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
//	free(arr);
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
//		env = env->next;
	}
	free (env);
}

/*void free_env(t_env	*env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = temp->next;
		free(temp);
	}
	free(env);
}*/