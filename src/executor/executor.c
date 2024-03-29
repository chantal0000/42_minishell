/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:35:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/03/28 13:23:10 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// TO DO:
	// - if there is a pipe check if built in or not
	// - add final env
	// - add resirections once they init in struct

/*
** Executes a simple command. If it's a built-in command, it's executed directly.
** Otherwise, it handles redirections and executes using execve().
*/
void	ft_simple_cmd(t_cmd *node, char **env)
{
	// only here  to test
	node->fd_in = -1;
	node->fd_out = -1;

	if ((node->fd_in) !=  -1)
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != -1)
		dup2(node->fd_out, STDOUT_FILENO);
    // check if builtin, if (ft_is_builtin(node) == 0)
	// {
		//printf("it's a build_in\n");
		//call built in fuction
	// }
    // else
    // {
        printf("it's not a built_in\n");
        // handle redirections?
        if (execute_cmd(env, node->cmd) == -1)
		{
			// handle error
			write(2, "Error in simple_cmd\n", 21);
		}
}

/*
** Handles the execution of the first command in a pipeline.
** Handles input/output redirection and executes the command.
** - 1 meaning there if no in/out file
** 1. if there is an infile we dup the files fd for stdin
** 2. if there is an outfile we dup the files fd for stdout
** 3. else we set the stdout to pipe_fd[1] (write end)
*/
int ft_pipe_first(t_cmd *node, int pipe_fd[2], char **env)
{
	// just to test
	node->fd_in = -1;
	node->fd_out = -1;
	//
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
		write (2, "in first_pipe pid 0\n", 21);
		if (execute_cmd(env, node->cmd) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
	// we only reach here if pid != 0, so if we are in parent
	return (handle_exit_status(pid));
}


/*
** Handles the execution of commands in the middle of a pipeline.
** Handles input/output redirection and executes the command.
*/
int ft_pipe_middle(t_cmd *node, int pipe_fd[2], int old_pipe_in, char **env)
{
	// just to test
	node->fd_in = -1;
	node->fd_out = -1;
	//
	// check in redirection,
	if (node->fd_in !=  -1)
		dup2(node->fd_in, STDIN_FILENO);
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
	close(old_pipe_in);
	close(pipe_fd[1]);
	int pid = fork();
	if (pid == 0)
	{
		if (execute_cmd(env, node->cmd) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
	return (handle_exit_status(pid));
	// new function built in vs cmd
}

/*
** Handles the execution of the last command in a pipeline.
** Handles input/output redirection and executes the command.
*/
int ft_pipe_last(t_cmd *node, int pipe_fd[2], int old_pipe_in, char **env)
{
	// just to test
	node->fd_in = -1;
	node->fd_out = -1;
	//
	if (node->fd_in !=  -1)
		dup2(node->fd_in, STDIN_FILENO);
	else
	{
		write (2, "dupping IN last pipe\n", 22);
		dup2(old_pipe_in, STDIN_FILENO);
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[1]);
	int pid = fork();
	if (pid == 0)
	{
		if (execute_cmd(env, node->cmd) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
	// wait(NULL);
	return (handle_exit_status(pid));
	// new function built in vs cmd
}

/*
** executor works with the *char[MAXARGS] -> took out split from my pipex exec
** need to change struct name based on our struct in minishell
** need to include wait to properly end
*/

/*
** Executes a sequence of commands, possibly connected by pipes.
** Determines the position of each command and executes it accordingly.
** 1. checks if its only one node, meaning a simple cmd
** 2. loop through nodes of linked list
** 3. checks if there is a next and prev node, meaning we are in middle
** 4. checks if we are in the first node
** 5. checks if we are in the last node
** 6. we save the old fd_in into old_pipe_in
** 7. move on to the next node in the linked list
*/

// env is just for now to test
int	ft_executor(t_cmd *node, char **env)
{
	int old_pipe_in = 0;
	int pipe_fd[2];
	int std_in = dup(STDIN_FILENO);
	int std_out = dup(STDOUT_FILENO);
	int	exit_status = 0;

	if (!node->next && !node->prev)
		ft_simple_cmd(node, env);
	while(node)
	{
		if (node->next && node->prev)
		{
			printf("entering middle pipe cmd is %s\n", node->cmd[0]);
			write(2, "\nentering middle pipe\n", 22);
			pipe(pipe_fd);
			exit_status = ft_pipe_middle(node, pipe_fd, old_pipe_in, env);
		}
		else if(node->next)
		{
			write(2, "\nentering first pipe\n", 21);
			pipe(pipe_fd);
			exit_status = ft_pipe_first(node, pipe_fd, env);
			printf("entering first pipe cmd is %s\n", node->cmd[0]);
		}
		else
		{
			write(2, "\nentering last pipe\n", 21);
			exit_status = ft_pipe_last(node, pipe_fd, old_pipe_in, env);
			printf("entering last pipe, cmd is %s\n", node->cmd[0]);
		}
		old_pipe_in = pipe_fd[0];
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		node = node->next;
	}
	// now everything is closed?
	close(std_in);
	close(std_out);
	//new added??
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (exit_status);
}

// int main(int argc, char **argv, char **env)
// {
	// t_exec	*first;
	// t_exec	*last;
	// t_exec	*middle1;
	// t_exec	*middle2;
//
	// first = malloc(sizeof(t_exec) * 1);
	// middle1 = malloc(sizeof(t_exec) * 1);
	// middle2 = malloc(sizeof(t_exec) * 1);
	// last = malloc(sizeof(t_exec) * 1);
//
	// int outfile = open("test2", O_TRUNC | O_CREAT | O_RDWR, 0644);
    // int infile = open("test_in.txt", O_RDONLY, 0644);
//
	// first->cmd[0] = strdup("ls");
	// first->cmd[1] = strdup("-l");
	// first->cmd[2] = NULL;
	// first->cmd[2] = strdup(NULL);
	// first->fd_in = -1;
	// first->fd_out = -1;
	// first->prev = NULL;
	// first->next = middle1;
    // // first->env = env;
//
	// middle1->cmd[0] = strdup("cat");
	// middle1->cmd[1] = NULL;
	// middle1->fd_in = -1;
	// middle1->fd_out = -1;
	// middle1->prev = first;
	// middle1->next = middle2;
    // // middle1->env = env;
//
//
	// middle2->cmd[0] = strdup("/bin/nl");
	// middle2->cmd[1] = NULL;
	// middle2->fd_in = -1;
	// middle2->fd_out = -1;
	// middle2->prev = middle1;
	// middle2->next = last;
    // // middle2->env = env;
//
//
	// last->cmd[0] = strdup("nl");
	// last->cmd[1] = NULL;
	// last->fd_in = -1;
	// last->fd_out = -1;
	// last->prev = middle2;
	// last->next = NULL;
    // // last->env = env;
//
//
	// return (ft_executor(first));

// ls | wc -> does not work?
// grep also doesnt work

// }

