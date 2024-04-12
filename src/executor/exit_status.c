/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:56:37 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/12 13:11:43 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	handle_exit_status(t_cmd *node)
{
	int	exit_status;
	int	status = 0;
	t_cmd *temp = node;
	exit_status = 0;
	printf("entering handle_exit_status\n");
	while (temp != NULL)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			// if (temp->next == NULL)
				exit_status = WEXITSTATUS(status);
		}
		temp = temp->next;
	}
	printf("exit_status: %d\n", exit_status);
	return (exit_status);
}
