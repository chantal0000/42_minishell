/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/23 16:26:51 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	free_cmdtree(t_cmd *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return ;
	if (tree->cmd[i])//frees exec cmds
	{
		while (tree->cmd[i])
		{
			free(tree->cmd[i]);
			i++;
		}
		free(tree->cmd);
	}
	if (tree->prev)
		free(tree->prev);
	if (tree->next)
		free(tree->next);
	if (tree->file_name)
		free(tree->file_name);
	if (tree->fd_in)
		close(tree->fd_in);
	if (tree->fd_out)
		close(tree->fd_out);
}*/
