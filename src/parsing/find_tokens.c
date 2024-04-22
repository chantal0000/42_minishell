/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:03 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/22 06:58:50 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_for_alligators(char **s)
{
	int	token;

	token = **s;
	if (**s == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			token = '+';
			(*s)++;
		}
	}
	else if (**s == '<')
	{
		(*s)++;
		if (**s == '<')
		{
			token = '-';
			(*s)++;
		}
	}
	return (token);
}

int	find_tokens(char **s, char **beg_of_file)
{
	int		token;
	char	*line;

	line = *s;
	while (*line != '\0' && is_whitespace(*line))
		line++;
	if (beg_of_file)
		*beg_of_file = line;
	token = *line;
	if (*line == '\0')
		return (token);
	else if (*line == '|' || *line == '(' || *line == ')')
		line++;
	else if (*line == '>' || *line == '<')
		token = check_for_alligators(&line);
//	else if (*line == 'e')
//		ft_check_for_echo(line);
	else
	{
		token = 'a';
		while (*line != '\0' && !is_whitespace(*line) && !is_token(*line))
			line++;
	}
	while (*line != '\0' && is_whitespace(*line))
		line++;
	*s = line;
	return (token);
}

/*char	ft_check_for_echo(char **s)
{
	if (ft_strncmp(*s, "echo", 4) == 0)
		{
			printf("hehe echo found\n");
			if (*s + 4)
//			cmd_tree = echo_cmds(cmd_tree, s);
//			break ;
		}
}*/