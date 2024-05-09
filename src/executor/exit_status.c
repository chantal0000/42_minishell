/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:56:37 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/09 14:32:36 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_exit_status(t_cmd *node)
{
	int		exit_status;
	int		status;
	t_cmd	*temp;

	exit_status = 0;
	status = 0;
	temp = node;
	while (temp != NULL)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
		}
		temp = temp->next;
	}
	return (exit_status);
}
