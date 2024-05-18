/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:03 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/18 07:54:59 by kbolon           ###   ########.fr       */
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

int	is_token(char s)
{
	char	*tokens;

	tokens = "|<>";//()";
	if (ft_strchr(tokens, s))
		return (1);
	return (0);
}

int	is_whitespace(char s)
{
	char	*whitespace;

	whitespace = " \n\t\r\v";
	if (ft_strchr(whitespace, s))
		return (1);
	return (0);
}

//iterates through any whitespaces found before cmd/token
//boolean, returns 1 if true (if next char is a token) and 0 for false
int	check_next_char(char **s, char token)
{
	char	*temp;

	if (!*s)
		return (0);
	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	*s = temp;
	if (**s != '\0' && **s == token)
		return (1);
	return (0);
}
