/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/29 17:33:33 by kbolon           ###   ########.fr       */
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
		temp = tree->next;
		if (tree->fd_in)
			close(tree->fd_in);
		if (tree->fd_out)
			close(tree->fd_out);
		if (tree->pid)
		{
			close(tree->pid);
//			kill(tree->pid, SIGKILL); should I use this?
		}
		// if (temp->m_env)
		// 	free_env(&temp->m_env);
		if (tree->file_name)
			free(tree->file_name);
		free_memory(tree->cmd);
		if (tree->heredoc_delimiter)
			free (tree->heredoc_delimiter);
		free_memory(tree->heredoc_content);
		free(tree);
		tree = temp;
	}
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

void	free_exp(t_exp *exp)
{
	t_exp	*temp;

	while (exp)
	{
		temp = exp;
		if (temp->exp_name)
			free(temp->exp_name);
		if (temp->exp_value)
			free (temp->exp_value);
		free (temp);
		exp = exp->next;
	}
	free (exp);
}
