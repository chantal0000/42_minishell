/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:32 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/03 16:53:39 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmdtree(t_cmd *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return ;
	if (tree->cmd)
		free_memory(tree->cmd);
//	if (tree->prev)
		free_nodes(tree->prev);
	if (tree->next)
		free(tree->next);
	if (tree->file_name)
		free(tree->file_name);
	if (tree->fd_in)
		close(tree->fd_in);
	if (tree->fd_out)
		close(tree->fd_out);
}
void	error_message(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

void	standard_error(void)
{
	write(2, "Error\n", 6);
	exit (0);
}

void	free_nodes(t_cmd *node)
{
	t_cmd	*temp;

	if (!node)
		return ;
	while (node)
	{
		temp = node;
		node = node -> next;
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