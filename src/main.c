/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/13 11:38:16 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** global variable for signal communication, needs to be init in main
*/
int	g_signal;

void	print_stack(t_cmd *root)
{
	t_cmd	*temp;

	temp = root;
	while (temp != NULL)
	{
		printf("\nnode[%d]\n", temp->index);
		printf("fd_in: %d\n", temp->fd_in);
		printf("fd_out: %d\n", temp->fd_out);
		printf("file_name: %s\n", temp->file_name);
		printf("token: %c\n", temp->token);
		printf("delimiter: %s\n", temp->heredoc_delimiter);
//		for (int i = 0; i < MAX_CONTENT_SIZE && temp->heredoc_content[i] != NULL; i++)
//		{
//			printf("heredoc content [%d]: %s\n", i, temp->heredoc_content[i]);
//		}
//		printf("node->data: %d\n", root-> data);
		for (int i = 0; i < MAXARGS && temp->cmd[i] != NULL; i++)
		{
			printf("cmd[%d]: %s\n", i, temp->cmd[i]);
		}
		temp = temp -> next;
	}
}

void	ft_execute(char *line, t_cmd **list, t_env **env_list, int *exit_status)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	parse_for_cmds(list, line);
	parse_cmds_for_expansions(list, *env_list, exit_status);
	print_stack(*list);
	*exit_status = ft_executor(*list, env_list);
	dup2(original_stdin, STDIN_FILENO);
		// close(original_stdin);
	dup2(original_stdout, STDOUT_FILENO);
		// close(original_stdout);
}

char	*read_command(t_cmd *list, t_env **env_list, int *exit_status)
{
	char	*line;

	while (1)
	{
		ft_init_signals();
		line = readline("minishell: ");
		if (!line)
		{
			ft_free_env_list(env_list);
			printf("exit\n");
			exit(0);
		}
		while (*line != '\0' && is_whitespace(*line))
			line++;
		if (*line == '\0')
			break ;
		else if (check_for_hanging_pipes(line) == 0)
		{
			add_history(line);
			ft_execute(line, &list, env_list, exit_status);
			list = NULL;
			return (line);
		}
	}
	return (line);
}


void	handle_exit(t_env *env_list, char *line)
{
	rl_clear_history();
	free(line);
	ft_free_env_list(&env_list);
}

int	main(int argc, char **argv, char **env)
{
	static char	*line;
	t_cmd		*list;
	t_env		*env_list;
	int			exit_status;

	(void)argc;
	(void)argv;
	g_signal = 0;
	line = NULL;
	list = NULL;
	exit_status = 0;
	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);
	}
	if (!env)
		return (0);
	env_list = fill_env_struct(env);
	while (1)
		line = read_command(list, &env_list, &exit_status);
	handle_exit(env_list, line);
	return (exit_status);
}
