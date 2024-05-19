/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 18:37:15 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** global variable for signal communication, needs to be init in main
*/
int	g_signal;

void	initialise_shell(int argc, char **env)
{
	g_signal = 0;
	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);
	}
	if (!env)
		exit(0);
	init_minishell(env);
}

void	clean_up(t_env *env)
{
	rl_clear_history();
	ft_free_env_list(&env);
}

void	run_shell(t_minishell *minishell_struct, int *exit_status)
{
	static char	*line;
	t_cmd		*list;

	line = NULL;
	list = NULL;
	while (1)
		line = read_command(list, minishell_struct, exit_status);
	free(list);
	list = NULL;
	close(minishell_struct->og_stdin);
	close(minishell_struct->og_stdout);
	free (line);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell_struct;
	int			exit_status;

	(void)argv;
	initialise_shell(argc, env);
	minishell_struct = init_minishell(env);
	run_shell(minishell_struct, &exit_status);
	clean_up(minishell_struct->env_list);
	return (exit_status);
}
