/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/18 12:55:16 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//if (s != '\0' means we have stopped before end of string
t_cmd	*parse_for_cmds(char *s)
{
	t_cmd	*cmd;

	if (!s)
		return (0);
	printf("parse for cmds\n");
	cmd = parse_for_pipe(&s);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	if (*s != '\0')
	{
		printf("check syntax\n");//check what bash returns
		return ((void *)0);
	}
//	ft_nul_cmds(cmd);//currently do it in each respective fcn
	printf("exit parse for cmds\n");
	return (cmd);
}

int	is_token(char s)
{
	char	*tokens;

	tokens = "|<>()";
	if (ft_strchr(tokens, s))
		return (1);
	return (0);
}

int	is_whitespace(char s)
{
	char	*whitespace;

	whitespace = " \n\t\r\v";
	if (ft_strchr(whitespace, s))
		return (1);//returns 1 if a whitespace
	return (0);
}

//iterates through any whitespaces found before cmd/token
//boolean, returns 1 if true (if next char is a token) and 0 for false
int	check_next_char(char **s, char token)
{
	while (**s != '\0' && is_whitespace(**s))
		(*s)++;
	if (*s && ft_strchr(*s, token))
		return (1);
	return (0);
}
