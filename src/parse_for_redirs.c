/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:20 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/25 18:55:41 by kbolon           ###   ########.fr       */
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
		token = find_tokens(s, &file_name);//is it <>+- and is following token an a (or filename?)
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
//	printf("exiting redir fcn\n");
	return (node);
}


