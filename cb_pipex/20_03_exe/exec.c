#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
** executor works with the *char[MAXARGS] -> took out split from my pipex exec
** need to change struct name based on our struct in minishell
**
*/



int	execute_cmd(char **env, char **cmd);
typedef struct s_exec t_exec;
typedef struct s_red t_red;

typedef struct s_red{
	int fd;

} t_red;
// typedef structure
struct s_exec{
	int		type;//cmd type (EXEC, PIPE, REDIR)
	char	*cmd[10];//for EXEC ONLY
	t_exec	*prev;//pointer to left branch (PIPE)
	t_exec	*next;//pointer to right branch (PIPE)
	char	*file_name;//pointer to beg file name for redir
//	char	*end_file;//pointer to space after file name for redir
	int		instructions;//instructions for redir (O_CREAT...)
	int		fd_in;//already open FD
	int		fd_out;
	// later on we need our own env
	char	**env;
};

int ft_is_builtin(t_exec *node);

void	ft_simple_cmd(t_exec *node)
{
    printf("in ft_simple_cmd\n");
    if (ft_is_builtin(node) == 0)
        printf("it's a build_in\n");
    else
    {
        printf("it's not a built_in\n");
        // handle redirections?
        if (execute_cmd(node->env, node->cmd) == -1)
		{
			// handle error
			write(2, "Error in simple_cmd\n", 21);
		}
    }
	// check if it is a builtin
    // redirections
	// otherwise execve()
}

/*
** -1 meaning there if no in/out file
** 1. if there is an infile we dup the files fd for stdin
** 2. if there is an outfile we dup the files fd for stdout
** 3. else we set the stdout to pipe_fd[1] (write end)
*/
void ft_pipe_first(t_exec *node, int pipe_fd[2])
{
	// char *cmd[2];

	// cmd[0] = node->cmd;
	// cmd[1] = NULL;
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
        // printf("in first_pipe pid 0\n");
		write (2, "in first_pipe pid 0\n", 21);
        // implemented my pipex executor
		if (execute_cmd(node->env, node->cmd) == -1)
		{
		//execve(node->cmd, cmd, NULL);
		// execve("/bin/ls", &"ls", NULL);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// function closing fdin and fd out
			exit(EXIT_FAILURE);

		exit(EXIT_FAILURE);
		}
		exit(0);
	}
	// wait(NULL);
	// fork
	// new function: built in vs cmd
	// execution
}

void ft_pipe_middle(t_exec *node, int pipe_fd[2], int old_pipe_in)
{
	// char *cmd[2];

	// cmd[0] = node->cmd;
	// cmd[1] = NULL;

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
         // implemented my pipex executor
		if (execute_cmd(node->env, node->cmd) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// function closing fdin and fd out
			exit(EXIT_FAILURE);
		//execve(node->cmd, cmd, NULL);
		// exit(0);
		}
	}
	// wait(NULL);
	// fork
	// new function built in vs cmd
	// execution
}

void ft_pipe_last(t_exec *node, int pipe_fd[2], int old_pipe_in)
{
	// char *cmd[2];

	// cmd[0] = node->cmd;
	// cmd[1] = NULL;
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
         // implemented my pipex executor
		if (execute_cmd(node->env, node->cmd) == -1)
		{
		// execve(node->cmd, cmd, NULL);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// function closing fdin and fd out
			exit(EXIT_FAILURE);
		}
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
void	ft_executor(t_exec *node)
{

	if (!node->next && !node->prev)
	{
		ft_simple_cmd(node);
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

int main(int argc, char **argv, char **env)
{
	t_exec	*first;
	t_exec	*last;
	t_exec	*middle1;
	t_exec	*middle2;

	first = malloc(sizeof(t_exec) * 1);
	middle1 = malloc(sizeof(t_exec) * 1);
	// middle2 = malloc(sizeof(t_exec) * 1);
	last = malloc(sizeof(t_exec) * 1);

	int outfile = open("test2", O_TRUNC | O_CREAT | O_RDWR, 0644);
    int infile = open("test_in.txt", O_RDONLY, 0644);

	first->cmd[0] = strdup("ls");
	first->cmd[1] = strdup("-l");
	first->cmd[2] = NULL;
	// first->cmd[2] = strdup(NULL);
	first->fd_in = -1;
	first->fd_out = -1;
	first->prev = NULL;
	first->next = middle1;
    first->env = env;

	middle1->cmd[0] = strdup("cat");
	middle1->cmd[1] = NULL;
	middle1->fd_in = -1;
	middle1->fd_out = -1;
	middle1->prev = first;
	middle1->next = last;
    middle1->env = env;


	// middle2->cmd = strdup("/bin/nl");
	// middle2->fd_in = -1;
	// middle2->fd_out = -1;
	// middle2->prev = middle1;
	// middle2->next = last;
    // middle2->env = *env;


	last->cmd[0] = strdup("nl");
	last->cmd[1] = NULL;
	last->fd_in = -1;
	last->fd_out = -1;
	last->prev = middle1;
	last->next = NULL;
    last->env = env;


	ft_executor(first);

// ls | wc -> does not work?
// grep also doesnt work
}

