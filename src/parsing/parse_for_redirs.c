/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/14 15:58:18 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//this function parses through the strings betwen pipes for redirs
//it looks for single <, > , and double << (heredocs), >>
t_cmd	*parse_for_redirections(t_cmd *node, char **s)
{
	int		token;
	char	*file_name;

	if ((**s == '<' || **s == '>') && **s != '\0')
	{
		file_name = NULL;
		token = find_tokens(s, &file_name);
		if (find_tokens(s, &file_name) != 'a')
			error_general("missing file");
		if (token == '-')
			ft_heredoc(node, file_name);
		else
			node->file_name = parse_line(file_name);
		if (token == '>')
			node = redir_cmd(node, O_WRONLY | O_CREAT | O_TRUNC, 1);
		if (token == '<')
			node = redir_cmd(node, O_RDONLY, 0);
		if (token == '+')
			node = redir_cmd(node, O_WRONLY | O_APPEND | O_CREAT, 1);
	}
	if (check_next_char(s, '<') || check_next_char(s, '>'))
		node = parse_mult_redir(node, s, file_name, token);
	return (node);
}

//this function parses the string after initial redirection
//should handle commands suchs nl << eof > out
t_cmd	*parse_mult_redir(t_cmd *node, char **s, char *file_name, int token)
{
	file_name = NULL;
	if (node->token == '-' )
		node = parse_outfile(node, s, file_name, token);
	else if (node->token == '+' )
	{
		if (node->fd_out > 0)
		{
			token = find_tokens(s, &file_name);
			if (find_tokens(s, &file_name) != 'a')
				error_general("missing file");
			if (token == '>')
				node = redir_cmd(node, O_WRONLY | O_CREAT | O_TRUNC, 1);
		}
	}
	else
		node = parse_for_redirections(node, s);
	return (node);
}

//this function parses after heredoc is found
t_cmd	*parse_outfile(t_cmd *node, char **s, char *file_name, int token)
{
	if (node->fd_in > 0)
	{
		token = find_tokens(s, &file_name);
		if (find_tokens(s, &file_name) != 'a')
			error_general("missing file");
		if (token == '>')
		{
			if (access(node->file_name, F_OK) != -1)
				node = redir_cmd(node, O_WRONLY | O_APPEND, 1);
			else
				node = redir_cmd(node, O_WRONLY | O_CREAT, 1);
		}
		else
			node->fd_out = -1;
	}
	else
		node = parse_for_redirections(node, s);
	return (node);
}
//this function opens the files and checks for errors
t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd_type)
{
	if (!node)
		return (NULL);
	if (fd_type == 0)
	{
		node->fd_in = open(node->file_name, instructions, 0777);
		node->fd_out = -1;
		check_access_and_fd(node, node->fd_in, 0);
	}
	else if (fd_type == 1)
	{
		node->fd_out = open(node->file_name, instructions, 0777);
		check_access_and_fd(node, 0, node->fd_out);
		node->fd_in = -1;
	}
	else if (!fd_type)
	{
		node->fd_in = -1;
		node->fd_out = -1;
	}
	return (node);
}

void	check_access_and_fd(t_cmd *cmd, int fd_in, int fd_out)
{
	t_cmd	*temp;

	temp = cmd;
	if (fd_in)
	{
		if (temp->fd_in < 0)
		{
			if (access(temp->file_name, F_OK | W_OK) == -1)
			{
				temp->fd_in = -1;
				perror("minishell: infile: No such file or directory");
				
			}
			else if (temp->fd_in < 0)
			{
//				close(temp->fd_in);
				temp->fd_in = -1;
				error_general("Error Opening file");
			}
		}
	}
	if (fd_out)
	{
		if (temp->fd_out < 0)
		{
			close(temp->fd_out);
			temp->fd_out = -1;
			error_general("Error Opening file");
		}
		if (access(temp->file_name, F_OK | W_OK) == -1)
		{
			close(temp->fd_out);
			temp->fd_out = -1;
			error_general("minishell: infile: No such file or directory");
		}
	}
	cmd = temp;
}
