/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/04 16:01:30 by kbolon           ###   ########.fr       */
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

int	main(int ac, char *av[], char *envp[])
{
	static char	*line;
	char		*s1;
	char		*token;

	if (ac != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
//not sure if we need the next 6 lines, if buffer has already
//been allocated, return the memory to free the pool
	line = (char *)NULL;
	if (line)
	{
		free(line);
		line = (char *)NULL;
	}
	line = readline("minishell: ");
	if (!line)
		return (0);
	while (line)
	{
		if (*line)
			add_history(line);
			build_cmd_tree(&line);
			//run/exec the cmds
		line = ("minishell: ");
	}
	free(line);
	return (0);
}
