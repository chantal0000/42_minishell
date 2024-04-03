/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/03 16:43:28 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_for_redirections(t_cmd *node, char **s)
{
	int		token;
	char	*file_name;

	file_name = NULL;
	if ((**s == '<' || **s == '>') && **s != '\0')
	{
		token = find_tokens(s, &file_name);
		if (find_tokens(s, &file_name) != 'a')
		{
			printf("missing file\n");//need to change to follow bash
			exit (1);
		}
		node->file_name = parse_line(strdup(file_name));
		if (token == '>')
			node = redir_cmd(node, O_WRONLY | O_CREAT | O_TRUNC, 1);//fd=1
		else if (token == '<')
			node = redir_cmd(node, O_RDONLY, 0);//fd=0
		else if (token == '+')
			node = redir_cmd(node, O_WRONLY | O_CREAT, 1);//fd=1
		else if (token == '-')
			node = redir_cmd(node, O_RDONLY, 0);//fd=0
		else
			return (NULL);
	}
	return (node);
}

t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd)
{
	if (!node)
		return (NULL);
	node->instructions = instructions;
	if (fd == 0)
	{
		node->fd_in = open(node->file_name, O_RDONLY, 0777);
		if (node->fd_in < 0)
		{
			printf("Error Opening Infile\n");//need to iterate through and close other fds
			close(node->fd_in);
			exit (1);
		}
		node->fd_out = -1;
	}
	else if (fd == 1)
	{
		node->fd_out = open(node->file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);
		if (node->fd_out < 0)
		{
			printf("Error Opening Outfile\n");
			close(node->fd_out);//need to iterate through and close other fds
			exit (1);
		}
		node->fd_in = -1;
	}
	else
	{
		node->fd_in = -1;
		node->fd_out = -1;
	}
	return (node);
}
