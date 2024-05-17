/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:14:31 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 12:29:47 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** function to find first node
*/
t_cmd	*first_node(t_cmd *node)
{
	if (node)
	{
		while (node->prev != NULL)
			node = node->prev;
	}
	return (node);
}

/*
** reset to std_in and std_out
*/
void	ft_reset_std(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
}

/*
** execution of cmds and free in case or error (127)
*/
void	ft_start_exec(t_env *env_list, t_cmd *node)
{
	if (execute_cmd(ft_env_list_to_array(env_list), node->cmd) == 127)
	{
		ft_free_env_list(&env_list);
		ft_free_cmd_struct(first_node(node));
		exit (127);
	}
}
