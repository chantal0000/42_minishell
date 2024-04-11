/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/11 16:06:34 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("instructions: %d\n", temp->instructions);
		printf("env: %s\n", temp->m_env->cmd_env);
		printf("pid: %d\n", temp->pid);
		printf("token: %c\n", temp->token);
//		printf("node->data: %d\n", root-> data);
		for (int i = 0; i < MAXARGS && temp->cmd[i] != NULL; i++)
		{
			printf("cmd[%d]: %s\n", i, temp->cmd[i]);
		}
//		printf("node->prev: %p\n", (void *)temp -> prev);
//		printf("node->next: %p\n\n", (void *)temp -> next);
		temp = temp -> next;
	}
}

int	main(int argc, char **argv, char **env)
{
	static char	*line;
//	char	*line = " grep lady < infile.txt | nl";
	t_cmd	*list;
//	int exit_status = 0;

	(void)argc;
	(void)argv;
	list = NULL;
/*	list = ft_init_struct();
	if (!list)
	{
		free(line);
		return (0);
	}*/
	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("Problems reading input");
			exit(1);
		}
		printf("line to be parsed: %s\n", line);
//		add_history(line);
		parse_for_cmds(&list, line, env);//need to add envp
		print_stack(list);
		if (!list)
		{
			free(line);
			return (0);
		}
		ft_executor(list);
		list = NULL; // here needs to be freed
	}
//	exit_status = ft_executor(list);
	free(line);
	free_cmdtree(list);
//	return (exit_status);
}
