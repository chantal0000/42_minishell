/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:03 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 18:12:22 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
/*int	check_for_nontokens(char **s)
{
	int	token;

	token = 'a';
	printf("in check_for_nontokens\n");
	while (**s != '\0' && !is_whitespace(**s) && !is_token(**s))
	{
		(*s)++;
		printf("token checker : %c\n", **s);
	}
	printf("out check_for_nontokens\n");
	return (token);
}*/

int	find_tokens(char **s, char **beg_of_file, char **end_of_file)
{
	int		token;
	char	*line;

	line = *s;
	while (*line != '\0' && is_whitespace(*line))
		line++;
	if (beg_of_file)
		*beg_of_file = line;
//	printf("beg:%c\n", **beg_of_file);
	token = *line;
	if (*line == '\0')
		return (token);
	else if (*line == '|' || *line == '(' || *line == ')')
		line++;
	else if (*line == '>' || *line == '<')
		token = check_for_alligators(&line);
	else
		token = 'a';
	while (*line != '\0' && !is_whitespace(*line) && !is_token(*line))
	{
		line++;
//		printf("token checker : %c\n", *line);
	}
//		token = check_for_nontokens(&line);
	if (end_of_file)
		*end_of_file = line;
//	printf("end:%c\n", **end_of_file);
	while (*line != '\0' && is_whitespace(*line))
		line++;//moves to space after token
	*s = line;
	return (token);
}
