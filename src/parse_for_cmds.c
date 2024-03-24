/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/24 19:29:14 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//if (s != '\0' means we have stopped before end of string
t_cmd	*parse_for_cmds(char *s)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	if (!s)
		return (0);
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		printf("failed init in parse cmd");
		exit (1);
	}
	cmd = parse_for_pipe(&s, &i);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	if (*s != '\0')
	{
		printf("check syntax\n");//check what bash returns
		return ((void *)0);
	}
//	ft_nul_cmds(cmd);//currently do it in each respective fcn
//	printf("exit parse for cmds\n");
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
	char	*temp;

	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	*s = temp;
	if (**s != '\0' && **s == token)
		return (1);
	return (0);
}
