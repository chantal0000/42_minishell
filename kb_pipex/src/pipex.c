/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:35:54 by kbolon            #+#    #+#             */
/*   Updated: 2023/10/30 12:13:19 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, int *fd, char **envp)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein < 0)
		error_message("Error Opening Infile", 1, fd, &filein);
	if (access(argv[1], F_OK | R_OK) == -1)
		error_message("Error with Infile Permissions: No access.", 1 ,\
			fd, &filein);
	if (dup2(filein, 0) == -1)
		error_message("Error dup2 FD stdin child", 1, fd, &filein);
	if (dup2(fd[1], 1) == -1)
		error_message("Error dup2 FD stdout child", 1, fd, &filein);
	close(fd[0]);
	close(filein);
	run_cmd(argv[2], envp);
}

void	parent(char **argv, int *fd, char **envp)
{
	int		fileout;

	fileout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fileout < 0)
		error_message("Error Opening Outfile", 1, fd, &fileout);
	if (access(argv[4], F_OK | W_OK) == -1)
		error_message("Error with Outfile permissions: no access.",\
			1, fd, &fileout);
	if (dup2(fileout, 1) == -1)
		error_message("Error dup2 FD stdout parent", 1, fd, &fileout);
	if (dup2(fd[0], 0) == -1)
		error_message("Error dup2 FD stdin parent", 1, fd, &fileout);
	close(fd[1]);
	close(fileout);
	run_cmd(argv[3], envp);
}

int	pipex(char **argv, char **envp)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) < 0)
		error_message("Error making pipe", 1, 0, 0);
	pid = fork();
	if (pid < 0)
		error_message("Error making fork", 1, 0, 0);
	if (pid == 0)
		child(argv, p_fd, envp);
	waitpid(pid, NULL, 0);
	parent(argv, p_fd, envp);
	close(p_fd[0]);
	close(p_fd[1]);
	return (0);
}

void	checkstring(char *s)
{
	if (s[0] == '\0')
	{
		errno = EINVAL;
		error_message("command is empty", 1, 0, 0);
	}
	if (s[0] == ' ')
	{
		errno = EINVAL;
		error_message("Please don't use spaces", 1, 0, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
	{
		checkstring(argv[2]);
		checkstring(argv[3]);
		pipex(argv, envp);
	}
	else
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);
	}
	return (0);
}
