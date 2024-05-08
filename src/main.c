/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/08 12:25:45 by kbolon           ###   ########.fr       */
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
//		printf("instructions: %d\n", temp->instructions);
		// printf("env: %s\n", temp->m_env->cmd_env);
//		printf("pid: %d\n", temp->pid);
		printf("token: %c\n", temp->token);
		printf("delimiter: %s\n", temp->heredoc_delimiter);
		for (int i = 0; i < MAX_CONTENT_SIZE && temp->heredoc_content[i] != NULL; i++)
		{
			printf("heredoc content [%d]: %s\n", i, temp->heredoc_content[i]);
		}
//		printf("node->data: %d\n", root-> data);
		for (int i = 0; i < MAXARGS && temp->cmd[i] != NULL; i++)
		{
			printf("cmd[%d]: %s\n", i, temp->cmd[i]);
		}
		temp = temp -> next;
	}
}
void	print_exp(t_exp *exp)
{
	t_exp	*temp;

	temp = exp;
	while (temp)
	{
		printf("exp name: %s\n", temp->exp_name);
		printf("exp value: %s\n", temp->exp_value);
		temp = temp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	static char	*line;
	t_cmd	*list;
	t_exp	*exp;
	t_env	*env_list;
	int original_stdout = dup(STDOUT_FILENO);
	int original_stdin = dup(STDIN_FILENO);
//	int exit_status = 0;

	(void)argc;
	(void)argv;
	g_signal = 0;
	exp = NULL;
	list = NULL;
	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
	if (!env)
		return (0);
	env_list = fill_env_struct(env);
	while (1)
	{
		ft_init_signals();
		line = readline("minishell: ");
		// this is basically ctrl D
		if (!line)
		{
			// free memory
			ft_free_env_list(env_list);
			// free(env_list);
			// while (env_list != NULL)
			// {
			// t_env *next = env_list->next;
			// free(env_list);
			// env_list = next;
			// }
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		parse_for_variables(&exp, &line);
//		print_exp(exp);
		if (line)
		{
			parse_for_cmds(&list, line);//need to add envp
//			print_stack(list);
			parse_cmds_for_expansions(&list, exp);
//			printf("\nafter expansion\n");
			print_stack(list);
		}
		if (list)
		{
			ft_executor(list, env_list);
			dup2(original_stdin, STDIN_FILENO);
			// close(original_stdin);
			dup2(original_stdout, STDOUT_FILENO);
			// close(original_stdout);
		}
		list = NULL; // here needs to be freed
		// free_cmdtree(list);
	}
	rl_clear_history();
//	HIST_ENTRY *entry = history_get(where_history());
//	printf("%s\n", entry->line);
//	exit_status = ft_executor(list);
//	print_exp(exp);
	free(line);
	// free_cmdtree(list);
	ft_free_env_list(env_list);
	free_exp(&exp);
	return (0);
}
