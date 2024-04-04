/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:21:20 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/04 11:21:50 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** exit with no options
** terminates the current shell session
** exit status -> 0 successful termination

** echo "hello" | exit | nl -> nothing happens cause exit ends
** echo "hallo" | exit | ls -> ls is still executed cause it does not depend
** on prev cmd

** does not exit if more than one numeric arg after exit
** "exit
** bash: exit: too many arguments"
** EXIT CODE 1

** if non numeric or (mixed) it exits with this msg:
** "exit
** bash: exit: hello: numeric argument required"
** EXIT CODE 2

** if only "exit"
** EXIT CODE 0
*/

int	ft_exit(t_cmd *cmd)
{
	// [exit] [1] [hello]
	char **exit_cmd = cmd->cmd;
	// const char *exit_cmd[] = { "exit", "               -42", NULL};
	// const char *exit_cmd[] = { "exit", "hello", "world", NULL};
	// const char *exit_cmd[] = { "exit", "1", "hello", NULL};
	//  char *exit_cmd[] = {"exit", NULL};

	int i = 0;
	// printf("%s\n", exit_cmd[0]);
	// printf("%s\n", exit_cmd[1]);
	// printf("%s\n", exit_cmd[2]);
	// check if exit_cmd[1] is numeric

	if (exit_cmd[1] != NULL)
	{
		while (exit_cmd[1][i])
		{
			while (exit_cmd[1][i] == 32)
				i++;
			if (exit_cmd[1][i] == '-' || exit_cmd[1][i] == '+')
				i++;
			// if non numeric exit but with error msg & exit code 2
			// ft_isdigit returns 0 if not a digit
			if ((ft_isdigit(exit_cmd[1][i]) == 0))
			{
				printf("exit_cmd[1][%d]: %c\n", i, exit_cmd[1][i]);
				printf("exit\n");
				printf("Error: exit: non-numeric argument for exit\n");
				exit (2);
			}
			i++;
		}
		if (exit_cmd[2] != NULL)
		{
			printf("exit\n");
			printf("Error: exit: too many arguments\n");
			// if yes and argv + 1 exists then error, return & code 1
			// what to do in this case?
			return (1);
		}
		else
		{
			printf("exit\n");
			exit (ft_atoi(exit_cmd[1]));
		}

	// if yes and !argv+1, exit & code is whatever we input
	}
	// there is no arg then exit & code 0
	else
	{
		printf("exit\n");
		exit(0);
	}
	return (0);
}