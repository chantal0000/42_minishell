#include <stdio.h>
#include "minishell.h"

#define DELIMITER "|<>()"
#define WHITESPACE " \n\t\r\v"

char	*ft_strchr(const char *s, int i)
{
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (0);
}

char	*find_tokens(char *input_str, char *tok_start, char *tok_end)
{
	char	*str;
	char	*token;	

	if (!input_str)
		return (NULL);
	str = input_str;
	//skip leading whitespaces
	while (str != (void *)0 && ft_strchr(WHITESPACE, *str))
		str++;
	if (tok_start != NULL && *tok_start == NULL)
	//if something in tok_start, update str pointer to it
		*tok_start = str;
	token = str;
	while (*str != '\0')
	{
		if (*str == '|' || *str == '(' || *str == ')')
			str++;
		else if (*str == '>')
		{
			str++;
			if (*str == '>')
			{
				token = '+';
				str++;
			}
		}
		else if (*str == '<')
		{
			str++;
			if (*str == '<')
			{
				token = '-';
				str++;
			}
		}
		else
		{
			token = 'a';
			//move to next delimiter
			while (*str != '\0' && !ft_strchr(DELIMITER, *str) && \
				!ft_strchr(WHITESPACE, *str))
				str++;
		}
		//update token_end pointer
		if (tok_end != (void *)0 )
			tok_end = str;
		//skip trailing whitespace
		while (str != (void *)0  && ft_strchr(WHITESPACE, *str))
			str++;
	}
	return (token);
}

int	main()
{
	char	*str = "(xxx | yyy) | zzz";
	char	*tok_start = NULL;
	char	*tok_end = NULL;
	char	token;

	token = *find_tokens(str, tok_start, tok_end);
	printf("Token: %c\n", token);
	if (tok_start != NULL && tok_end != NULL)
	{
		printf("Extracted token: ");
		for (char *p = tok_start; p != tok_end; p++)
			putchar(*p);
		putchar('\n');
	}
	return (0);
}