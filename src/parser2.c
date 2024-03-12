/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:03 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/11 19:06:56 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
int	check_for_nontokens(char **s)
{
	int	token;

	token = 'a';
	while (**s != '\0' && !is_whitespace(**s) && !is_token(**s))
		(*s)++;
	return (token);
}

int	find_tokens(char **s, char **beg_of_file, char **end_of_file)
{
	int		token;
	char	*line;

	line = *s;
	while (*line != '\0' && is_whitespace(*line))
		line++;
	if (beg_of_file != NULL)
		*beg_of_file = line;
	token = *line;
	if (*line == '\0')
		return (token);
	else if (*line == '|' || *line == '(' || *line == ')')
		line++;
	else if (*line == '>' || *line == '<')
		token = check_for_alligators(&line);
	else
		token = check_for_nontokens(&line);
	if (end_of_file)
		*end_of_file = line;
	while (*line != '\0' && is_whitespace(*line))
		line++;
	*s = line;
	return (token);
}

//When a struct cmd* is received, it points to a base struct w/ limited 
//fields. To manipulate extended fields in structures like t_exec or 
//t_redir, the pointer must be cast to the appropriate type. 
//This casting informs the compiler of the pointer's actual structure type, 
//enabling access to both base and extended fields.

//This approach facilitates polymorphism in C, enabling functions like 
//ft_nul_cmds to operate on various command types through a 
//common interface. By examining the type field and casting accordingly, 
//the function ensures type safety while handling diverse command structures.
t_cmd	*ft_nul_cmds(t_cmd *cmd)
{
	t_cmd	*pipe_cmd;
	t_redir	*redir_cmd;

	if (!cmd)
		return ((void *)0);
	if (cmd->type == EXEC)
		cmd = (t_cmd *)ft_exec_cmd(cmd);
	if (cmd->type == PIPE)
	{
		pipe_cmd = (t_cmd *)cmd;
		{
			ft_nul_cmds(pipe_cmd->left);
			ft_nul_cmds(pipe_cmd->right);
		}
	}
	if (cmd->type == REDIR)
	{
		redir_cmd = (t_redir *)cmd;
		ft_nul_cmds(redir_cmd->cmd);
		redir_cmd->end_file = 0;
	}
	return ((t_cmd *)cmd);
}
