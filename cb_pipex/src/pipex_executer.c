/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:12:31 by chbuerge          #+#    #+#             */
/*   Updated: 2024/02/19 14:39:59 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


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
// test main to see if i can execute commands
int main (int argc, char **argv, char **env)
{
	execute_cmd(env, argv[1]);
	return (0);
}
