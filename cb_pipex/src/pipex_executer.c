/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:12:31 by chbuerge          #+#    #+#             */
/*   Updated: 2024/02/29 18:19:11 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


/*
** join the path to one string and add the name of the command to create the
** whole cmd_path
*/
char	*get_command_path(char *cmd, char **path)
{
	char	*tmp_path;
	char	*cmd_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	(path);
	return (NULL);
}

/*
** locate the absolute path of a given commmand by searching through the
** directories listed in the environment variable
*/
char	*find_cmd_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, 58);
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (get_command_path(cmd, path));
}

/*
** 'execve' loads and exectues a new program referred to by
** the specific file path in the current process, replaces the current process
*/
int	execute_cmd(char **env, char *cmd)
{
	char	**split_cmd;
	char	*cmd_path;
	int		i;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(split_cmd[0], env);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "Command '", 9);
		while (cmd[i])
		{
			write(STDERR_FILENO, &cmd[i], 1);
			i++;
		}
		write(STDERR_FILENO, "' not found\n", 12);
		// free array function from pipex?
		//if (split_cmd)
		//	free_array(split_cmd);
		return (-1);
	}
	if (execve(cmd_path, split_cmd, env) != 1)
		exit (127);
	return (127);
}



// test with 2 commands

void	handle_cmd2(char **env, char **input, int fd_array[2])
{
	int		fd;
	char	*cmd;

	cmd = input[2];
	//fd = open(input[1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	// if (fd == -1)
	// {
	// 	ft_printf("pipex: %s: Permission denied\n", input[4]);
	// 	ft_error_after_pipe("", fd_array, EXIT_FAILURE);
	// }
	// do i need the comment below if i dont write into anywhere
	//dup2(fd, STDOUT_FILENO);
	dup2(fd_array[0], STDIN_FILENO);
	close(fd_array[1]);
	if (execute_cmd(env, cmd) == -1)
	{
		close(fd_array[0]);
		close(fd_array[1]);
		close(fd);
		exit(127);
	}
}

void	handle_cmd1(char **env, char **input, int fd_array[2])
{
	int		fd;
	char	*cmd;

	cmd = input[1];
	// if (access(input[1], F_OK) == -1)
	// {
	// 	ft_printf("pipex: %s: No such file or directory\n", input[1]);
	// 	ft_error_after_pipe("", fd_array, EXIT_FAILURE);
	// }
	// if (access(input[1], R_OK) == -1)
	// {
	// 	ft_printf("pipex: %s: Permission denied\n", input[1]);
	// 	ft_error_after_pipe("", fd_array, EXIT_FAILURE);
	// }
	//fd = open(input[1], O_RDONLY);
	// do i need the line below if i dont have a file / redirection?
	//dup2(fd, STDIN_FILENO);
	dup2(fd_array[1], STDOUT_FILENO);
	close(fd_array[0]);
	if (execute_cmd(env, cmd) == -1)
	{
		close(fd_array[0]);
		close(fd_array[1]);
		close(fd);
		exit(EXIT_FAILURE);
	}
}


// test main to see if i can execute commands
int main (int argc, char **argv, char **env)
{
	int fd_array[2];
	int id1 = 0;
	int id2 = 0;

	pipe(fd_array);
	id1 = fork();
	if (id1 == 0)
	{

		handle_cmd1(env, argv, fd_array);
		//execute_cmd(env, argv[1]);
	}
	if (id2 == 0)
	{
		handle_cmd2(env, argv, fd_array);
		//execute_cmd(env, argv[2]);
	}

	return (0);
}

// nl < input.txt > output1.txt > text


// redirection?

// char *** ls -la | wc
// char ** ls -la
// char *ls

// char ***commands
// int number of commands
// char *infile path
// char *outfile path

// init_piptes(nb_commands)

// init_redirection

// if (i == 0)
// {
// 	if (infile path = 0)
// 		infile_fd = STDIN_FILENO;
// 	else
// 		infile_fd = open(infile_path);
// }
// else if (i == nb_commands - 1)
// {
// 	if (outfile_path = 0)
// 		outfile_fd = STDOUT_FILENO
// 	else
// 		outfile_fd = open(outfile_path)
// }


// else
// {
// 	infile_fd =- pipe[]
// }
