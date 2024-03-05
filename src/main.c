/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/05 14:37:30 by kbolon           ###   ########.fr       */
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

/*int	main(int ac, char *av[], char *envp[])
{
	static char	*line = "ls -l | wc";
	char 		*s1;
	t_cmd		*cmd;
	
	s1 = ft_strdup(line);
	if (ac != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
	cmd = build_cmd_tree(s1);
	line = readline("minishell: ");
	if (!line)
		return (0);
	while (line)
	{
		if (*line)
		{
			add_history(line);
			build_cmd_tree(&line);
			//run/exec the cmds
		}
		line = ("minishell: ");
	}
//	free(line);
	free(s1);
	return (0);
}*/

int	main()
{
	char	*line = "> ls -l | wc";
	char	*s2;
	char	*delim = "<>|()";
	char	*token;
	int		token2;

	s2 = ft_strdup(line);
	parse_for_cmds(s2);
//	token2 = find_tokens(s2);
//	printf("%c\n", token2);

//	free(line); //need this for readline
//	free(s1);
	free(s2);
	return (0);
}