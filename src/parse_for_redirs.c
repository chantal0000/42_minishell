/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 18:32:00 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*t_cmd	*parse_for_redirections(t_cmd *cmd, char **s)
{
//	int		token;
	char	*beg_of_file;
	char	*end_of_file;

	printf("now parsing for redirections\n");
	while (check_next_char(s, '<') || check_next_char(s, '>'))
	{
		printf("in while loop\n");
//		token = find_tokens(s, 0, 0);
//		printf("token: %d\n", token);
		find_tokens(s, 0, 0);
		if (find_tokens(s, &beg_of_file, &end_of_file) != 'a')
		{
			printf("missing file");//need to change to follow bash
			return (NULL);
		}
		if (**s == '>')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_WRONLY | O_CREAT | O_TRUNC, 1);//fd=1
		else if (**s == '<')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_RDONLY, 0);//fd=0
		else if (**s == '+')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file,  O_WRONLY | O_CREAT, 1);//fd=1
		else if (**s == '-')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_RDONLY, 0);//fd=0
		else
			return (NULL);
	}
	return (cmd);
}*/


t_cmd	*redir_cmd(t_cmd *cmd, char *beg_file, char *end_file, int instructions, int fd)
{
	t_redir	*redirection;

	redirection = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redirection)
		return (NULL);
	redirection->type = REDIR;
	redirection->cmd = cmd;
	redirection->beg_file = beg_file;
	redirection->end_file = end_file;
	redirection->instructions = instructions;
	redirection->fd = fd;
	return ((t_cmd *)redirection);
}
