/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/27 15:28:17 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//if (s != '\0' means we have stopped before end of string
void	parse_for_cmds(t_cmd **cmd, char *s)
{
	int		index;
	t_exp	*exp;

	index = 0;
	exp = NULL;
	if (!s)
		return ;
	s = check_for_quotes(s);
	parse_for_pipe(&s, cmd, 0, &index);
	update_fd(*cmd);
//	exp = ft_find_var_declarations(cmd);
//	ft_find_var_expansions(cmd, exp);
	while (exp)
	{
		printf("exp name: %s\n", exp->exp_name);
		printf("expvalue : %s\n", exp->exp_value);
		exp = exp->next;
	}
	// fill_env_struct(*cmd, env);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	if (*s != '\0')
	{
		printf("check syntax\n");//check what bash returns
		return ;
	}
	restore_pipes_and_spaces(*cmd);
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

char	*check_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
	in_single = 0;
	in_double = 0;
	temp = s;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != '\\' && !in_double)
			in_single = !in_single;
		else if (*temp == '\"' && (*temp - 1) != '\\' && !in_single)
			in_double = !in_double;
		else if (*temp == '|' && (in_single || in_double))
			*temp = '\xFD';
		else if (*temp == ' ' && (in_single || in_double))
			*temp =  '\xFE';
		temp++;
	}
	if (in_single || in_double == -1)
	{
		printf("open quotes found, can't parse");
		exit (1);
	}
	return (s);
}

