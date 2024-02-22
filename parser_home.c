/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 07:17:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/22 07:40:43 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_cmds(char *cmd)
{
//	char 	**tokens_array;
//	char	token;
	int		buffer;
	int		i;

	if (!cmd || !cmd[0])
		return ;
	i = 0;
	buffer = TOKEN_BUF;
//	parse_quotes_and_pipes(cmd);
//	tokens_array = (char *) malloc(buffer * sizeof(char));
//	if (!tokens_array)
//		return ;
//	token = ft_strtok(cmd, DELIMITER);
/*	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		if (i >= buffer)
		{
			buffer += TOKEN_BUF;
			tokens = 
		}
	}
	pipe_split = ft_split(cmd, '|');
	printf("pipe replace\n");
	while (pipe_split[i])
	{
		printf("%s\n", pipe_split[i]);
		i++;
	}
	i = 0;
	restore_pipes(cmd);
	printf("pipe restore\n");
	if (!pipe_split)
		return ;
	while (pipe_split[i])
		i++;
	tokens = (char **) malloc (sizeof(char) * i + 1);
	if (!tokens)
	{
		free_memory(pipe_split);
		return ;
	}
	while (k < i)
	{
		tokens[k] = *ft_split(pipe_split[k], ' ');
		if (!tokens[k])
		{
			free_memory(pipe_split);
			free (tokens[k]);
			return ;		
		}
		k++;
	}
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}*/
}

void	parse_quotes_and_pipes(char *str)
{
	int		in_quotes;
	int		in_brackets;

	in_quotes = 0;
	in_brackets = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			in_quotes = !in_quotes; //toggles between 0 and 1
		else if (*str == '(')
			in_brackets = 1;
		else if (*str == ')')
			in_brackets = 0;
		if (*str == '|' && !in_quotes && !in_brackets) //if pipe is found and in brackets/quotes then replace
			*str = '\xFD'; //Unicode for replacement char
		str++;
	}

}

void	restore_pipes(char *str)
{
	while (*str)
	{
		if (*str == '\xFD')
			*str = '|';
		str++;
	}
}

char	*ft_strtok(char *str, char *delimiter)
{
	int			len;
	static char	*ptr;
	char		*token;

	if (str != NULL)
		ptr = str;
	if (*ptr == '\0')
		return (NULL); //return NULL if no more tokens
	token = ptr;
	while (*ptr != '\0')
	{
		if (ft_strchr(delimiter, *ptr) != NULL)
		{
			*ptr++ = '\0';
			return (token);
		}
		ptr++;
	}
	return (token);
}
int	find_tokens(char *pstr, char *ptok, char *endtok, char *pstrend)
{
	char	whitespace;
	char	tokens;
	char	*str;
	int		i;

	whitespace = " \n\t\r\v";
	tokens = "|<>()&";//do we do &?? I don't think so
	str = pstr;
	while (ptok < pstrend && ft_strchr(whitespace, *str))//or can I do != '\0'?
		str++;
	if (ptok)//if something in ptok, update str pointer to it
		*ptok = str;
	i = *str;
	if (*str == '\0)
}