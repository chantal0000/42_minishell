/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/27 14:09:32 by kbolon           ###   ########.fr       */
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
	while (root != NULL)
	{
		printf("node->current_position: %d\n", root->index);
		printf("node->current_position: %p\n", root);
//		printf("node->data: %d\n", root-> data);	
		for (int i = 0; i < MAXARGS && root->cmd[i] != NULL; i++) 
		{
			printf("cmd[%d]: %s\n", i, root->cmd[i]);
		}
		printf("node->prev: %p\n", (void *)root -> prev);
		printf("node->next: %p\n\n", (void *)root -> next);
		root = root -> next;
	}
}

/*int	main(int ac, char **av, char *envp[])
{
	static char	*line;
	t_cmd		*cmd;

	if (ac != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
	void(ac);
	void(av);
	line = readline("minishell: ");
	if (!line)
		return (0);
	while (line)
	{
		if (*line)
		{
			add_history(line);
			cmd = *parse_for_cmds(line, envp);
			printf("back in main fcn\n");
			ft_executor(cmd);
			//run/exec the cmds
		}
		line = ("minishell: ");
	}

//	rl_clear_history();
	free(line);
	return (0);
}*/

int	main()
{
	char	*line = "ls | wc | cat | la ";
	t_cmd	*list;
	t_env	*env;
//	char	*envp = "address";

	list = NULL;
	env = NULL;
//	cmd_tree = init_head(envp);
//	if (!cmd_tree)
//		return (0);
	printf("line to be parsed: %s\n", line);
	list = parse_for_cmds(line);//need to add envp
	if (!list)
		return (0);
	printf("\n");
	print_stack(list);
	return (0);
}
