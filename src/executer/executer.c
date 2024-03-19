/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:42:25 by chbuerge          #+#    #+#             */
/*   Updated: 2024/03/19 09:57:49 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_simple_cmd(t_cmd *node)
// {
// 	// check if it is a builtin
// 	// otherwise execve()
// }

/*
** -1 meaning there if no in/out file
** 1. if there is an infile we dup the files fd for stdin
** 2. if there is an outfile we dup the files fd for stdout
** 3. else we set the stdout to pipe_fd[1] (write end)
*/
void ft_pipe_first(t_cmd *node, int pipe_fd[2])
{
	char *cmd[2];

	cmd[0] = node->cmd[0];
	cmd[1] = NULL;


	// check redirection,
	if ((node->fd_in) !=  -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		write (2, "dupping IN first pipe\n", 23);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	// close irrelevant stuff
	// added close otherwise ls | wc didnt work
	close(pipe_fd[1]);
	int pid = fork();
	if (pid == 0)
	{
		execve(node->cmd[0], cmd, NULL);
		// execve("/bin/ls", &"ls", NULL);
		exit(0);
	}
	// wait(NULL);
	// fork
	// new function: built in vs cmd
	// execution
}

void ft_pipe_middle(t_cmd *node, int pipe_fd[2], int old_pipe_in)
{
	char *cmd[2];

	cmd[0] = node->cmd[0];
	cmd[1] = NULL;

	// check in redirection,
	if (node->fd_in !=  -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
	}
	else
	{
		write (2, "MIDDLE PIPE: dupping IN pipe\n", 30);
		dup2(old_pipe_in, STDIN_FILENO);
	}

	// check out redirection,
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		write (2, "MIDDLE PIPE: dupping OUT pipe\n", 31);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}

	// close irrelevant stuff
	// added close otherwise ls | wc didnt work
	close(pipe_fd[1]);
	int pid = fork();
	if (pid == 0)
	{
		execve(node->cmd[0], cmd, NULL);
		// exit(0);
	}
	// wait(NULL);
	// fork
	// new function built in vs cmd
	// execution
}

void ft_pipe_last(t_cmd *node, int pipe_fd[2], int old_pipe_in)
{
	char *cmd[2];

	cmd[0] = node->cmd[0];
	cmd[1] = NULL;
	// check in redirection,
	if (node->fd_in !=  -1)
		dup2(node->fd_in, STDIN_FILENO);
	else
	{
		write (2, "dupping IN last pipe\n", 22);
		dup2(old_pipe_in, STDIN_FILENO);
	}

	// check out redirection,
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	// close irrelevant stuff
	// added close otherwise ls | wc didnt work
	close(pipe_fd[1]);
	int pid = fork();
	if (pid == 0)
	{
		execve(node->cmd[0], cmd, NULL);
	}
	// wait(NULL);
	// fork
	// new function built in vs cmd
	// execution
}

/*
** 1. checks if its only one node, meaning a simple cmd
** 2. loop through nodes of linked list
** 3. checks if there is a next and prev node, meaning we are in middle
** 4. checks if we are in the first node
** 5. checks if we are in the last node
** 6. we save the old fd_in into old_pipe_in
** 7. move on to the next node in the linked list
*/
void	ft_executor(t_cmd *node)
{
	printf("IN EXECUTER\n");

	if (!node->next && !node->prev)
	{
		//ft_simple_cmd(node);
		printf("simple cmd\n");
	}

	// int num_nodes = ft_count_nodes(node);
	// int fd_array[num_nodes - 1][2];

	int old_pipe_in;
	int pipe_fd[2];
	int std_in = dup(STDIN_FILENO);
	int std_out = dup(STDOUT_FILENO);

	while(node)
	{
		if (node->next && node->prev)
		{
			printf("entering middle pipe cmd is %s\n", node->cmd[0]);
			write(2, "\nentering middle pipe\n", 22);
			pipe(pipe_fd);
			ft_pipe_middle(node, pipe_fd, old_pipe_in);
		}
		else if(node->next)
		{
			write(2, "\nentering first pipe\n", 21);
			pipe(pipe_fd);
			ft_pipe_first(node, pipe_fd);
			printf("entering first pipe cmd is %s\n", node->cmd[0]);
		}
		else
		{
			write(2, "\nentering last pipe\n", 21);
			ft_pipe_last(node, pipe_fd, old_pipe_in);
			printf("entering last pipe, cmd is %s\n", node->cmd[0]);
		}
		old_pipe_in = pipe_fd[0];
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		node = node->next;
	}
	//new added??
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
