/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/25 13:04:42 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_for_redirections(t_cmd *cmd, char **s, int *i, char **envp)
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
		file_name = parse_line(ft_strdup(file_name));
		if (token == '>')
			cmd = init_redir(cmd, file_name, O_WRONLY | O_CREAT | O_TRUNC, 1);//fd=1
		else if (token == '<')
			cmd = init_redir(cmd, file_name, O_RDONLY, 0);//fd=0
		else if (token == '+')
			cmd = init_redir(cmd, file_name, O_WRONLY | O_CREAT, 1);//fd=1
		else if (token == '-')
			cmd = init_redir(cmd, file_name, O_RDONLY, 0);//fd=0
		else
			return (NULL);
		cmd->index = *i;
		cmd->env = envp;
		(*i)++;
	}
	return (cmd);
}


