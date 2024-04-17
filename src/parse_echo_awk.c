/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/17 16:57:58 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_echo(t_cmd *cmd_tree, char **s)
{
	int		i;
	int		len;
	t_cmd	*temp;

	i = 0;
	temp = cmd_tree;
	len = 0;
//	printf("echo fcn\n");
	if (ft_strncmp(temp->cmd[i], "echo", 4) == 0)
	{
		i++;
//		printf("echo fcn 1\n");
		len = parse_quotes_for_echo(*s);
//		printf("echo fcn 2\n");
		temp->cmd[i] = strndup(*s, len + 1);
//		printf("echo fcn 3 \n");
	}
	i++;
	temp->cmd[i] = NULL;
	cmd_tree = temp;	
	*s += len;
	printf("s before exit echo fcn%s\n", *s);
	return (cmd_tree);
}

char	*parse_line_echo(char *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] != '\0' && (!is_whitespace(arr[i]) && !is_token(arr[i])))
		i++;
	arr[i] = '\0';
	return (arr);
}

int	is_echo_token(char s)
{
	char	*tokens;

	tokens = "\'\"";
	if (ft_strchr(tokens, s))
		return (1);
	return (0);
}

int	parse_quotes_for_echo(char *s)
{
	int		in_single;
	int		in_double;
	int		i;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
	i = 0;
	in_single = 0;
	in_double = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && (s[i - 1]) != '\\' && !in_double)
		{
			i++;
			in_single = !in_single;
			while (s[i] != '\'' && (s[i - 1]) != '\\' && s[i] != '\0' && s[i] != '|')
				i++;
			return (i);
		}
		else if (s[i] == '\"' && (s[i - 1]) != '\\' && !in_single)
		{
			i++;
			in_double = !in_double;
			while (s[i] != '\"' && (s[i - 1]) != '\\' && s[i] != '\0' && s[i] != '|')
				i++;
			return (i);
		}
		else
		{
			while (s[i] != '|' && s[i] != '\0')
				i++;
//			return (i);
		}
	}
	return (i);
}
