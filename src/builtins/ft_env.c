/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:35:02 by chbuerge          #+#    #+#             */
/*   Updated: 2024/03/28 15:02:49 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** env command in Unix-like operating systems prints a list of environment
** variables and their values
*/

void	ft_env(t_cmd *cmd)
{
	while (cmd->m_env)
	{
		printf("%s\n", cmd->m_env->cmd_env);
		cmd->m_env = cmd->m_env->next;
	}

}


