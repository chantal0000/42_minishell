/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/04 16:26:15 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char *s)
{
	char	*tokens;

	tokens = "|<>()";
	if (ft_strchr(tokens, *s))
		return (1);
	return (0);
}

int	is_whitespace(char *s)
{
	char	*whitespace;

	whitespace = " \n\t\r\v";
	if (ft_strchr(whitespace, *s))
		return (1);//returns 1 if a whitespace
	return (0);
}

t_cmd	*ft_parse_for_pipe(char *str)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if(!str)
		return (0);
	cmd = build_cmd_tree(str);//builds tree and saves pointer to cmd
	if (check_next_char(&str, '|'))
	{
		find_tokens(&str, 0, 0);
		temp = ft_parse_for_pipe(str);
//cmd is left subtree and temp right subtree and if more pipes, 
//will create a new pipe node		
		cmd = pipe_cmd(cmd, temp);
	}
	return (cmd);
}

int	check_next_char(char **s, char token)//boolean, returns 1 if true and 0 for false
{
//	char	*s;

//	s = *pstr;
	while (*s != (void *)0 && is_whitespace(*s))
		(*s)++;
//	*pstr = s;
	if (*s && ft_strchr(*s, token))
		return (1); //if next non-whitespace is a token, return true
	return (0);
}

void	free_cmd_tree(t_exec *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return;
	if (tree->cmd[i])
	{
		while (tree->cmd[i])
		{
			free(tree->cmd[i]);
			i++;
		}
		free(tree->cmd);
	}
	i = 0;
	if (tree->options[i])
	{
		while (tree->options[i])
		{
			free(tree->options[i]);
			i++;
		}
		free(tree->options);
	}
}
