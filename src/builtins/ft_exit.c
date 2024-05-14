/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:21:20 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/14 14:25:10 by chbuerge         ###   ########.fr       */
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
void	ft_handle_nodigi(t_cmd *cmd, t_env *env_list)
{
	printf("exit\n");
	printf("Error: exit: non-numeric argument for exit\n");
	ft_free_cmd_struct(cmd);
	ft_free_env_list(&env_list);
	exit (2);
}

void	ft_free_exit(t_cmd *cmd, t_env **env_list)
{
	printf("exit\n");
	ft_free_cmd_struct(cmd);
	ft_free_env_list(env_list);
}

int	ft_exit(t_cmd *cmd, t_env **env_list)
{
	char	**exit_cmd;
	int		i;
	int		exit_status;

	exit_cmd = cmd->cmd;
	i = 0;
	exit_status = 0;

	if (exit_cmd[1] != NULL)
	{
		while (exit_cmd[1][i])
		{
			while (exit_cmd[1][i] == 32)
				i++;
			if (exit_cmd[1][i] == '-' || exit_cmd[1][i] == '+')
				i++;
			if ((ft_isdigit(exit_cmd[1][i]) == 0))
				ft_handle_nodigi(cmd, *env_list);
			i++;
		}
		if (exit_cmd[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		exit_status = ft_atoi(exit_cmd[1]);
		ft_free_exit(cmd, env_list);
		exit (exit_status);
	}
	ft_free_exit(cmd, env_list);
	exit (0);
}
