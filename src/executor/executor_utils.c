/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:12:31 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/05 16:07:46 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//#include "minishell.h"
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/stat.h>
// #include <fcntl.h>

char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *str, char c);
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
	// free_array(path);
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
int	execute_cmd(char **env, char **cmd)
{
	char	**split_cmd;
	char	*cmd_path;
	int		i;

	i = 0;
	// take out this split and change char *cmd to char **cmd
	// split_cmd = ft_split(cmd, ' ');

	write (2, "in execute_cmd\n", 16);

	split_cmd = cmd;
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
		return (127);
	}
	if (execve(cmd_path, split_cmd, env) == -1)
		return (127);
	return (0);
}
