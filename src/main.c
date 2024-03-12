/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 15:25:42 by kbolon           ###   ########.fr       */
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

void print_cmd(t_cmd *cmd)
{
	t_exec	*exec_cmd;
	t_cmd	*pipe_cmd;
	int		i;

	if (cmd == NULL)
		return ;
	i = 0;
	if (cmd->type == EXEC)
	{
		exec_cmd = (t_exec *)cmd;
		printf("Command: ");
		while (exec_cmd->cmd[i])
		{
			printf("%s ", exec_cmd->cmd[i]);
			i++;
		}
		printf("\n");
	}
	else if (cmd->type == PIPE)
	{
		pipe_cmd = (t_cmd *)cmd;
		print_cmd(pipe_cmd->left);
		print_cmd(pipe_cmd->right);
	}
	else
//		printf("Unknown command type\n");
	return ;
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
	char	*line = " (ls -a) | wc";
//	int		token;
	t_cmd	cmd;
	
	cmd = *parse_for_cmds(line);
	print_cmd(&cmd);
/*	printf("\nMine\n");
	token = find_tokens(&line, NULL, NULL);
	printf("token is: %c\n", token);
	while (token != '\0')
	{
	 	printf("token is: %c\n", token);
		token = find_tokens(&line, NULL, NULL);
	}*/

	
	return (0);
}