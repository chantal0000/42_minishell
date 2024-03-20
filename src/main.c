/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/20 15:06:57 by chbuerge         ###   ########.fr       */
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
	char	*line = "ls | wc";
//	int		token;
	t_cmd	*cmd;

	printf("line to be parsed: %s\n", line);
	cmd = parse_for_cmds(line);
	while (cmd->next != NULL)
	{
		printf("cmd->type: %d\n", cmd->type);
		cmd = (*cmd).next;
	}
	printf("back in main fcn\n");
	// execution here?
	ft_executor(cmd);

//	free_cmd(&cmd);
	return (0);
}
