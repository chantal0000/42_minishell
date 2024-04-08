/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:56:37 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/08 10:14:36 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// #include <sys/types.h>
// #include <sys/wait.h>

int	handle_exit_status(t_cmd *node)
{
	int	exit_status;
	int	status = 0;
	int i = 0;

	exit_status = 0;
	printf("entering handle_exit_status\n");
	while (node != NULL)
	{
		printf("entering LOOP in handle_exit_status\n");
		waitpid(node->pid, &status,WUNTRACED);
		printf("pid in exit %d\n", node->pid);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
		}
		printf("exit_status: %d\n", exit_status);
		i++;
		node = node->next;
	}
	printf("counter %d\n", i);
	// printf("exit_status: %d\n", exit_status);
	return (exit_status);
}
