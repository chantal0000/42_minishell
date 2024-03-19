/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/19 06:45:27 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_for_redirections(t_cmd *node, char **s)
{
	int		token;
	char	*file_name;

//	printf("now parsing for redirs\n");
	file_name = NULL;
	if ((**s == '<' || **s == '>') && **s != '\0')
	{
		token = find_tokens(s, &file_name);//is it <>+- and is following token an a (or filename?)
		if (find_tokens(s, &file_name) != 'a')
		{
			printf("missing file\n");//need to change to follow bash
			exit (1);
		}
		node->file_name = parse_line(ft_strdup(file_name));
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
	node->type = REDIR;
	node->instructions = instructions;
	if (fd == 0)
		node->fd_in = fd;
	else if (fd == 1)
		node->fd_out = fd;
	return (node);
}
