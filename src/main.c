/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/03 16:20:36 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_message(char *str, int i, int *fd, int *fd2)
{
	if (fd || fd2)
	{
		close(*fd);
		close(*fd2);
	}
	perror(str);
	exit (i);
}
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
	t_cmd		*list;
//	char	*line = "ls | wc | cat ";

	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
	(void)argc; // Suppress unused parameter warning
	(void)argv; // Suppress unused parameter warning
//	(void)env;
	line = readline("minishell: ");
//	if (!line)
//		return (0);
//	while (line)
//	{
//		if (*line)
//		{
//			add_history(line);
	parse_for_cmds(&list, line, env);//need to add envp
	if (!list)
		return (0);
	print_stack(list);
//			ft_executor(cmd);
			//run/exec the cmds
//		}
//		line = ("minishell: ");
	ft_executor(list, env);
//	rl_clear_history();
	free(line);
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	char	*line = "ls | wc | cat ";
	t_cmd	*list;
//	t_env	*env;
//	char	*envp = "address";
(void)argc; // Suppress unused parameter warning
(void)argv; // Suppress unused parameter warning
(void)env;
	list = NULL;
//	env = NULL;
	printf("line to be parsed: %s\n", line);
	parse_for_cmds(&list, line);//need to add envp
	if (!list)
		return (0);
	printf("\n");
	print_stack(list);
	printf("main BEFORE executor\n");
//	ft_executor(list, env);
	printf("main AFTER executor\n");
	return (0);
}*/
