/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:35:50 by kbolon            #+#    #+#             */
/*   Updated: 2023/11/01 11:28:27 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_memory(char **free_my_paths)
{
	size_t	i;

	i = 0;
	while (free_my_paths[i] != NULL)
	{
		free(free_my_paths[i]);
		i++;
	}
	free (free_my_paths);
}

char	*make_path(char **all_path, char **cmd_split)
{
	int		i;
	char	*path_part;
	char	*cmd_path_full;

	i = -1;
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		cmd_path_full = ft_strjoin(path_part, cmd_split[0]);
		free(path_part);
		if (access(cmd_path_full, F_OK | X_OK) == 0)
			return (cmd_path_full);
		free(cmd_path_full);
	}
	return (0);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*cmd_path_full;
	char	**allpath;
	char	**cmd_split;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			allpath = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (!allpath)
		error_message("PATH not found", 1, 0, 0);
	cmd_split = ft_split(cmd, ' ');
	cmd_path_full = make_path(allpath, cmd_split);
	free_memory(allpath);
	free_memory(cmd_split);
	if (!cmd_path_full)
	{
		free(cmd_path_full);
		return (NULL);
	}
	return (cmd_path_full);
}

void	run_cmd(char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	if (!cmd || !cmd[0])
		error_message("command is empty", 127, 0, 0);
	cmd_split = ft_split(cmd, 32);
	if (!cmd_split)
		error_message("command is empty or splitting failed", 127, 0, 0);
	path = get_path(cmd_split[0], envp);
	if (!path)
	{
		free_memory(cmd_split);
		write(STDERR_FILENO, "command not found\n", 18);
		exit(127);
	}
	if (execve(path, cmd_split, envp) == -1)
	{
		free_memory(cmd_split);
		error_message("execve failed, command not found", 127, 0, 0);
	}
}

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
