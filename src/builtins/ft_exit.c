/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:21:20 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/21 13:44:32 by chbuerge         ###   ########.fr       */
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
void	ft_handle_nodigi(t_cmd *cmd, t_env *env_list, t_minishell *minishell_struct)
{
	printf("exit\n");
	printf("Error: exit: non-numeric argument for exit\n");
	ft_free_cmd_struct(cmd);
	ft_free_env_list(&env_list);
	free(minishell_struct);
	exit (2);
}

int	ft_exit(t_cmd *cmd, t_minishell *minishell_struct)
{
	int		exit_status;

	exit_status = 0;
	if (cmd->cmd[1] != NULL)
	{
		ft_exit_helper(cmd, minishell_struct);
		if (cmd->cmd[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		exit_status = ft_atoi(cmd->cmd[1]);
	}
	ft_exit_free(minishell_struct, cmd, exit_status);
	return (0);
}

void	ft_exit_helper(t_cmd *cmd, t_minishell *minishell_struct)
{
	int	i;

	i = 0;
	while (cmd->cmd[1][i])
	{
		while (cmd->cmd[1][i] == 32)
			i++;
		if (cmd->cmd[1][i] == '-' || cmd->cmd[1][i] == '+')
			i++;
		if ((ft_isdigit(cmd->cmd[1][i]) == 0))
			ft_handle_nodigi(cmd, minishell_struct->env_list, minishell_struct);
		i++;
	}
}
