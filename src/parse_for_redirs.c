/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/10 19:02:28 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_for_redirections(t_cmd *node, char **s)
{
	int		token;
	int		i;
	char	*file_name;

	file_name = NULL;
	i = 0;
	printf("string in redir1: %s \n", *s);
	if ((**s == '<' || **s == '>') && **s != '\0')
	{
		token = find_tokens(s, &file_name);
		printf("token1 %s: \n", file_name);
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
		{
//			node = redir_cmd(node, O_RDONLY | O_CREAT, 0);//fd=0 do I need create here?
			printf("token: %c\n", token);
			printf("string in redir: %s \n", *s);
			node = ft_heredoc(node, s);
			printf("delimiter after heredoc: %s\n", node->heredoc_delimiter);
		}
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
		node->fd_out = open(node->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777); // | S_IRUSR | S_IWUSR,
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

t_cmd	*ft_heredoc(t_cmd *cmd, char **s)
{
	char	*delimiter;
	int		i;

	delimiter = NULL;
	i = 0;
	find_tokens(s, &delimiter);
	cmd->heredoc_delimiter = t_strdup(delimiter);
//	cmd->heredoc_delimiter = parse_line(ft_strdup(delimiter));
	while (i < MAX_CONTENT_SIZE)
	{
		cmd->heredoc_content[i] = ft_calloc(MAX_CONTENT_SIZE, sizeof(char));
		if (!cmd->heredoc_content[i])
		{
			printf("Memory allocation failed in heredoc\n");
			exit (1);
		}
	}
	i = 0;
	while (ft_strcmp(*s, cmd->heredoc_delimiter) != 0 && \
		i < MAX_CONTENT_SIZE - 1)
	{
		cmd->heredoc_content[i] = ft_strdup(*s);
		if (!cmd->heredoc_content[i])
		{
			printf("problems copying content for heredoc\n");
			exit (1);
		}
		i++;
		(*s)++;
	}
//	(*s)++;
	cmd->heredoc_content[i] = NULL;
	return (cmd);
}
