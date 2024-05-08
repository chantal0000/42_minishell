/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/08 16:56:10 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*parse_for_redirections(t_cmd *node, char **s)
{
	int		token;
	char	*file_name;

	if ((**s == '<' || **s == '>') && **s != '\0')
	{
		file_name = NULL;
		token = find_tokens(s, &file_name);
		if (find_tokens(s, &file_name) != 'a')
			error_message("missing file", 1);
		if (token == '-')
//		{
//			node->heredoc_delimiter = parse_line(strdup(file_name));
			ft_heredoc(node, file_name);
//		}
		else
			node->file_name = parse_line(strdup(file_name));
		if (token == '>')
			node = redir_cmd(node, O_WRONLY | O_CREAT | O_TRUNC, 1);
		if (token == '<')
			node = redir_cmd(node, O_RDONLY, 0);
		if (token == '+')
			node = redir_cmd(node, O_WRONLY | O_APPEND | O_CREAT, 1);
	}
	if (check_next_char(s, '<') || check_next_char(s, '>'))
		node = parse_multiple_redirections(node, s, file_name, token);
	return (node);
}

t_cmd	*parse_multiple_redirections(t_cmd *node, char **s, char *file_name, int token)
{

	file_name = NULL;
	if (node->token == '-' )
	{
		if (node->fd_in > 0)
		{
			token = find_tokens(s, &file_name);
			if (find_tokens(s, &file_name) != 'a')
				error_message("missing file", 1);
			if (token == '>')
			{
				if (access(node->file_name, F_OK) != -1)
					node = redir_cmd(node, O_WRONLY | O_APPEND, 1);
				else
					node = redir_cmd(node, O_WRONLY | O_CREAT, 1);
			}
			if (token == '<')
				node = redir_cmd(node, O_RDONLY, 0);
		}
	}
	else if (node->token == '+' )
	{
		if (node->fd_out > 0)
		{
			token = find_tokens(s, &file_name);
			if (find_tokens(s, &file_name) != 'a')
				error_message("missing file", 1);
			if (token == '>')
				node = redir_cmd(node, O_WRONLY | O_CREAT | O_TRUNC, 1);
			if (token == '<')
				node = redir_cmd(node, O_RDONLY, 0);
		}
	}
	else
		node = parse_for_redirections(node, s);
	return (node);
}

t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd)
{
	if (!node)
		return (NULL);
	node->instructions = instructions;
	if (fd == 0)
		node->fd_in = ft_open_fcn(node, instructions, 0777);
	else if (fd == 1)
		node->fd_out = ft_open_fcn(node, instructions, 0777);
	else if (!fd)
	{
		node->fd_in = -1;
		node->fd_out = -1;
	}
	return (node);
}

int		ft_open_fcn(t_cmd *node, int instructions, int num)
{
	int		fd;

	fd = open(node->file_name, instructions, num);
	if (fd < 0)
	{
		printf("Error Opening file\n");
		close(fd);
		exit (1);
	}
	return (fd);
}

void	ft_create_temp_file(char ** heredoc_content, t_cmd *cmd)
{
	char	temp_file[] = "/tmp/tempfile21008";
	ssize_t bytes_written;
	int i = 0;

	bytes_written = -1;
	cmd->fd_in = open(temp_file,  O_RDWR | O_CREAT | O_TRUNC, 0777);
	printf("fd_in on heredoc 1: %d\n", cmd->fd_in);
	if (cmd->fd_in == -1)
	{
		perror("Failed to create temporary file");
		return;
	}
	while(heredoc_content[i])
	{
		bytes_written = write(cmd->fd_in, heredoc_content[i], ft_strlen(heredoc_content[i]));
		write(cmd->fd_in, "\n", 1);
		i++;
	}

	if (bytes_written == -1) {
		perror("Failed to write to temporary file");
		// close(fd);
		unlink(temp_file); // Delete the temporary file
		return;
	}
	cmd->file_name = "/tmp/tempfile21008";
	close(cmd->fd_in);
	cmd->fd_in = open(cmd->file_name, O_RDONLY, 0777);
	printf("fd_in on heredoc 2: %d\n", cmd->fd_in);
	printf("fd_out on heredoc 2: %d\n", cmd->fd_out);
	if (cmd->fd_in == -1)
	{
		perror("Failed to reopen tempfile");
		// close(fd);
		unlink(temp_file); // Delete the temporary file
		return;
	}
	// change this
	// cmd->fd_out = -1;
	// Close the file descriptor
	// close(cmd->fd_in);
}

void	ft_heredoc(t_cmd *cmd, char *file_name)
{
	static char	*str;
	char		*heredoc_content[MAX_CONTENT_SIZE];
	int			i;

	i = 0;
	cmd->heredoc_delimiter = parse_line(strdup(file_name));
	signal(SIGINT, ft_init_signals_heredoc);
	while (i < MAX_CONTENT_SIZE)
	{
		str = readline("> ");
		if (!str)
		{
			printf("minishell: warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strcmp(str, cmd->heredoc_delimiter) == 0)
			break ;
		heredoc_content[i] = ft_strdup(str);
		if (!heredoc_content[i])
			error_message("Memory allocation failed in heredoc", 1);
		i++;
	}
	heredoc_content[i] = NULL;
	ft_create_temp_file(heredoc_content, cmd);
	free_memory(heredoc_content);
}

char	*make_string(char **s)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)ft_calloc(1, sizeof(char));
	if (!temp)
	{
		printf("problem allocating mem for string\n");
//		free_memory(s);
		exit (1);//return?
	}
	while (s[i] != NULL)
	{
		temp = ft_strjoin(temp, s[i]);
		if (!temp)
		{
			printf("problem allocating mem for string\n");
//			free_memory(s);
			exit (1);//return?
		}
		i++;
	}
	return (temp);
}
