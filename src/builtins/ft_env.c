/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:35:02 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/11 11:40:24 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** env command in Unix-like operating systems prints a list of environment
** variables and their values
*/

int	ft_env(t_cmd *cmd)
{
	t_env	*current;

	current = cmd->m_env;
	while (current)
	{
		printf("%s\n", current->cmd_env);
		current = current->next;
	}
	return (0);
}
