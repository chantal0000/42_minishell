/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/23 15:49:26 by kbolon           ###   ########.fr       */
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

/*void print_cmd(t_cmd *cmd)
{
	t_exec	*exec_cmd;
	t_cmd	*pipe_cmd;
	int		i;

	printf("Now in print command \n");
	if (cmd == NULL)
		return ;
	i = 0;
	if (cmd->type == EXEC)
	{
		printf("Now in print EXEC command \n");
		exec_cmd = (t_exec *)cmd;
		while (exec_cmd->cmd[i] != NULL)
		{
			printf("Command: %s \n", exec_cmd->cmd[i]);
			i++;
		}
		printf("\n");
		printf("Now in exiting EXEC command \n");
	}
	else if (cmd->type == PIPE)
	{
		printf("Now in print PIPE command \n");
		pipe_cmd = (t_cmd *)cmd;
		print_cmd(pipe_cmd->left);
		print_cmd(pipe_cmd->right);
		printf("Now in exiting print PIPE command \n");
	}
	else
//		printf("Unknown command type\n");
	printf("Now exiting print command \n");
	return ;
}*/

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
			cmd = *parse_for_cmds(line);
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
	char	*line = "ls | wc | cat";
//	int		token;
	t_head	*cmd_tree;
	char	**envp;
//	int i = 0;

	cmd_tree = NULL;
	envp = NULL;
	cmd_tree = init_head(envp);
	if (!cmd_tree)
		return (0);
	printf("line to be parsed: %s\n", line);
	cmd_tree->cmd = parse_for_cmds(line);
	if (!cmd_tree->cmd)
	{
		free (cmd_tree);
		return (0);
	}
//	printf("back in main fcn\n");
/*	while (cmd_tree->next != NULL)
	{
		printf("cmd node [%d]: \n", i);
//		printf("node [%d]:\n", cmd_tree->index);
		printf("cmd->type: %d\n", cmd_tree->type);
//		printf("cmd->prev->type: %d\n", cmd_tree->prev->type);
		printf("cmd->prev: %s\n", *cmd_tree->prev->cmd);
		printf("cmd->next: %s\n", *cmd_tree->next->cmd);
		i++;
		cmd_tree = cmd_tree->next;
	}

	// execution here?
	ft_executor(cmd_tree);*/
	free(cmd_tree);
	return (0);
}
