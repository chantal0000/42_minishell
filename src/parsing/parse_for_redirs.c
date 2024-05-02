/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/02 17:42:33 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (token == '-')
		{
			node->heredoc_delimiter = parse_line(strdup(file_name));
			ft_heredoc(node);
//			node = redir_cmd(node, O_RDONLY | O_CREAT, 0);//fd=0 do I need create here?
			// make_string(node->heredoc_content);
		}
		else
			node->file_name = parse_line(strdup(file_name));
		if (token == '>')
			node = redir_cmd(node, O_WRONLY | O_CREAT | O_TRUNC, 1);//fd=1
		if (token == '<')
			node = redir_cmd(node, O_RDONLY, 0);//fd=0
		if (token == '+')
			node = redir_cmd(node, O_WRONLY | O_CREAT, 1);//fd=1
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
		node->fd_out = open(node->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (node->fd_out < 0)
		{
			printf("Error Opening Outfile\n");
			close(node->fd_out);
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

//NOTE FOR KAREN
// fd below seems to be overwritten somewhere?


// I think the problem is that at some point after this maybe it is set to -1
// also need to delete the file at some point but when?
// do we need to do something about mult heredocs, what if cat <<eof | wc <<eof
void	ft_create_temp_file(t_cmd *cmd)
{
	char	temp_file[] = "/tmp/tempfile21008";
	ssize_t bytes_written;
	int i = 0;
	int fd = -1;
	bytes_written = -1;
	fd = open(temp_file,  O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Failed to create temporary file");
		return;
	}
	while(cmd->heredoc_content[i])
	{
		bytes_written = write(fd, cmd->heredoc_content[i], ft_strlen(cmd->heredoc_content[i]));
		write(fd, "\n", 1);
		i++;
	}
	if (bytes_written == -1) {
        perror("Failed to write to temporary file");
        // close(fd);
        unlink(temp_file); // Delete the temporary file
        return;
    }
	cmd->file_name = "/tmp/tempfile21008";
	close(fd);
	cmd->fd_in = open(cmd->file_name, O_RDONLY, 0777);
	// cmd->fd_in = fd;
    // Close the file descriptor
    // close(fd);
}


void	ft_heredoc(t_cmd *cmd)
{
	static char	*str;
	int			i;

	i = 0;
	while (i < MAX_CONTENT_SIZE)
	{
		str = readline("> ");
		if (!str)
		{
			printf("Problems reading input for heredoc");
			exit(1);
		}
		if (ft_strcmp(str, cmd->heredoc_delimiter) == 0)
			break ;
		cmd->heredoc_content[i] = ft_strdup(str);
		str = ft_strdup(str);
		ft_create_temp_file(cmd);
		if (!cmd->heredoc_content[i])
		{
			printf("Memory allocation failed in heredoc\n");
			exit (1);
		}
		i++;
	}
	cmd->heredoc_content[i] = NULL;
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
