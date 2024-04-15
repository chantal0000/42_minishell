/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/15 17:25:46 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//if (s != '\0' means we have stopped before end of string
void	parse_for_cmds(t_cmd **cmd, char *s, char **env)
{
	int	index;

	index = 0;
	if (!s)
		return ;
	s = parse_for_quotes(s);
	printf("after parsing quotes: %s\n", s);
	parse_for_pipe(&s, cmd, 0, &index);
	update_fd(*cmd);
	fill_env_struct(*cmd, env);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	if (*s != '\0')
	{
		printf("check syntax\n");//check what bash returns
		return ;
	}
	restore_pipes(*cmd);
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

char	*parse_for_quotes(char *s)
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
		temp++;
	}
	return (s);
}

/*t_cmd	*ft_parse_quotes(t_cmd *cmd, char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;
	int		i;

	s = parse_for_quotes(s);
	i = 0;
	while (i < MAXARGS)
	{
		cmd->cmd[i] = NULL;
		i++;
	}
	in_single = 0;
	in_double = 0;
	while (*s)
	{
		if (*s == '\'' && (*s - 1) != '\\' && !in_double)
		{
			temp = s;
			in_single = !in_single;
		}
		else if (*s == '\"' && (*s - 1) != '\\' && !in_single)
			in_double = !in_double;
		s++;
	}
	if (!check_next_char(&s, '\'') && (*temp - 1) != '\\' && !in_double)
	{
		printf("missing closing quote\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("\nGROUP CLOSED\n");
	find_tokens(&s, 0);
	cmd = parse_for_redirections(cmd, &s);
	return (cmd);
}

t_cmd	*parse_for_groups(char **s)
{
	t_cmd	*cmd;
//	int		token;

	if (!**s || !s)
		return (0);
//	printf("%s\n", *s);
//	printf("now checking for groups\n");
	if (!check_next_char(s, '('))
	{
		printf("missing prev bracket");
		exit (1);
	}
//	token = find_tokens(s, 0);
	find_tokens(s, 0);
//	printf("string in group %s\n", *s);
//	printf("token in group %c\n", token);
	cmd = parse_for_pipe(s);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("\nGROUP CLOSED\n");
	find_tokens(s, 0);
	cmd = parse_for_redirections(cmd, s);
	return (cmd);
}*/