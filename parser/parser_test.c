/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:30:02 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/20 07:03:48 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <editline/readline.h>

#define TOKEN_BUF 100
#define DELIMITER "|<>&()"

void	parse_quotes_and_pipes(char *str);
void	restore_pipes(char *str);
int		ft_strlen(char *str);
char	*ft_strtok(char *str, char *delimiter);

char	*ft_strchr(const char *str, int ch)
{
	while (*str != (char)ch)
	{
		if (!*str)
			return (0);
		str++;
	}
	return ((char *)str);
}

static int	ft_release(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (-1);
}

static int	ft_count_words(const char *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == charset || str[i + 1] == '\0') == 1
			&& (str[i] == charset || str[i] == '\0') == 0)
			words++;
		i++;
	}
	return (words);
}

static void	ft_write_word(char *dest, const char *from, char charset)
{
	int	i;

	i = 0;
	while ((from[i] == charset || from[i] == '\0') == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_write_split(char **split, const char *str, char charset)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == charset || str[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (str[i + j] != charset && str[i + j] != '\0')
				j++;
			split[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (split[word] == 0)
				return (ft_release(split, word - 1));
			ft_write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(const char *str, char c)
{
	char	**res;
	int		words;

	words = ft_count_words(str, c);
	res = (char **) malloc (sizeof(char *) * (words + 1));
	if (res == 0)
		return (0);
	res[words] = 0;
	if (ft_write_split(res, str, c) == -1)
		return (0);
	return (res);
}

void	free_memory(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}



int	main()
{
	char	*line;
	char	*s1;
	char	*s2;
	char	*delim = "<>|&()";
	char	*token;
	char	*token2;

	line = readline("minishell: ");
	if (!line)
		return (0);
	s1 = strdup(line);
	s2 = strdup(line);
	parse_quotes_and_pipes(s1);
	token = ft_strtok(s1, delim);
	printf("Mine\n");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, delim);
	}
	parse_quotes_and_pipes(s2);
	token2 = strtok(s2, delim);
	printf("\nReal\n");
	while (token2 != NULL)
	{
		printf("%s2\n", token);
		token2 = strtok(NULL, delim);
	}
	free(line);
	free(s1);
	free(s2);
	return (0);
}