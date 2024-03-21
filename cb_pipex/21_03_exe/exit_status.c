/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:56:37 by chbuerge          #+#    #+#             */
/*   Updated: 2024/03/21 15:02:16 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	handle_exit_status(int pid)
{
	int	exit_status;

	exit_status = 0;
	waitpid(pid, &exit_status, WUNTRACED);
	return (exit_status);
}
