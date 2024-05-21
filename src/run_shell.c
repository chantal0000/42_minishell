/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:11:33 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/21 14:45:55 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_execute(char *line, t_cmd **list, t_minishell *minishell_struct, \
// 			int *exit_status)
// {
// 	parse_for_cmds(list, line);
// 	parse_cmds_for_expansions(list, minishell_struct->env_list, exit_status);
// 	restore_pipes_and_spaces(*list);
// 	*exit_status = ft_executor(*list, minishell_struct);
// 	dup2(minishell_struct->og_stdin, STDIN_FILENO);
// 	dup2(minishell_struct->og_stdout, STDOUT_FILENO);
// }

// char	*read_input(t_minishell *minishell_struct)
// {
// 	char	*line;

// 	ft_init_signals();
// 	line = readline("minishell: ");
// 	if (!line)
// 	{
// 		printf("exit\n");
// 		ft_exit_free(minishell_struct, NULL, 0);
// 	}
// 	while (*line != '\0' && is_whitespace(*line))
// 		line++;
// 	return (line);
// }

// char	*process_command(char *line, t_cmd **list, \
// 			t_minishell *minishell_struct, int *exit_status)
// {
// 	if (*line == '\0')
// 	{
// 		free (line);
// 		return (NULL);
// 	}
// 	else if (check_for_hanging_pipes(line) == 0 && \
// 		check_redirection_file_names (line) == 0)
// 	{
// 		add_history(line);
// 		ft_execute(line, list, minishell_struct, exit_status);
// 		*list = NULL;
// 		return (line);
// 	}
// 	return (line);
// }

// char	*read_command(t_cmd *list, t_minishell *minishell_struct, \
// 			int *exit_status)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = read_input(minishell_struct);
// 		line = process_command(line, &list, minishell_struct, exit_status);
// 		if (!line)
// 			break ;
// 	}
// 	return (line);
// }

// t_minishell	*init_minishell(char **env)
// {
// 	t_minishell	*minishell_struct;

// 	minishell_struct = malloc(sizeof(t_minishell));
// 	minishell_struct->og_stdin = dup(STDIN_FILENO);
// 	minishell_struct->og_stdout = dup(STDOUT_FILENO);
// 	minishell_struct->env_list = fill_env_struct(env);
// 	return (minishell_struct);
// }
