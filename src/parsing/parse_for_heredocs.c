/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:14:02 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/10 17:40:54 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_create_temp_file(char **heredoc_content, t_cmd *cmd)
{
	char	temp_file[] = "/tmp/tempfile21008";
	ssize_t	bytes_written;
	int		i;
	int		len;

	i = 0;
	len = 0;
	bytes_written = -1;
	cmd->fd_in = open(temp_file,  O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (cmd->fd_in == -1)
		error_general("Failed to create temporary file");
	while (heredoc_content[i])
	{
		len = ft_strlen(heredoc_content[i]);
		bytes_written = write(cmd->fd_in, heredoc_content[i], len);
		write(cmd->fd_in, "\n", 1);
		i++;
	}
	if (bytes_written == -1)
		error_temp("Failed to write to temporary file", temp_file);
	cmd->file_name = "/tmp/tempfile21008";
	close(cmd->fd_in);
	cmd->fd_in = open(cmd->file_name, O_RDONLY, 0777);
	if (cmd->fd_in == -1)
		error_temp("Failed to reopen tempfile", temp_file);
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
			error_message("Memory allocation failed in heredoc", 1, 0);
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
		error_general("problem allocating mem for string");
	while (s[i] != NULL)
	{
		temp = ft_strjoin(temp, s[i]);
		if (!temp)
			error_general("problem allocating mem for string");
		i++;
	}
	return (temp);
}
