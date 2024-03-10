/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/10 07:13:52 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd_tree(t_exec *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return ;
	if (tree->cmd[i])
	{
		while (tree->cmd[i])
		{
			free(tree->cmd[i]);
			i++;
		}
		free(tree->cmd);
	}
	i = 0;
	if (tree->options[i])
	{
		while (tree->options[i])
		{
			free(tree->options[i]);
			i++;
		}
		free(tree->options);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->left)
		free(cmd->left);
	if (cmd->right)
		free(cmd->right);
	free(cmd);
}