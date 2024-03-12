/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 14:54:04 by kbolon           ###   ########.fr       */
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
	ft_nul_cmds(cmd);
	return (cmd);
}

//cmd is left subtree and temp right subtree and if more pipes, 
//will create a new pipe node
t_cmd	*parse_for_pipe(char **str)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (!**str || !str)
		return (0);
	printf("now parsing for pipes\n");
	cmd = NULL;
	temp = build_cmd_tree(str);
	if (check_next_char(str, '|'))
	{
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL, NULL);
		cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (NULL);	
		cmd->type = PIPE;
		cmd->left = temp;
		cmd->right = parse_for_pipe(str);
		printf("\nEXIT PIPE PARSE1\n");
		return (cmd);
	}
	printf("\nEXIT PIPE PARSE2\n");
	return (temp);
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

