/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:56:37 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 12:28:52 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** function to find first node
*/
t_cmd	*last_node(t_cmd *node)
{
	if (node)
	{
		while (node->next != NULL)
			node = node->next;
	}
	return (node);
}

int	count_nodes(t_cmd *node)
{
	int	count;

	count = 0;
	if (node)
	{
		while (node)
		{
			count++;
			node = node->next;
		}
	}
	return (count);
}

int	handle_exit_status(t_cmd *node)
{
	int		exit_status;
	int		status;
	int		num_cmds;
	int		i;
	t_cmd	*last;

	exit_status = 0;
	i = 0;
	status = 0;
	num_cmds = count_nodes(node);
	last = last_node(node);
	while (i < num_cmds)
	{
		if (waitpid(0, &status, 0) == last->pid)
		{
			exit_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_status);
}
