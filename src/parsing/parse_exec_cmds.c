/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/07 06:23:03 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_line(char *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] != '\0' && (!is_whitespace(arr[i]) && !is_token(arr[i])))
		i++;
	arr[i] = '\0';
	return (arr);
}

t_cmd	*init_exec_cmds(t_cmd *cmd_tree, char **s, char *non_token)
{
	int		i;
	int		token;

	i = 0;
	token = 0;
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		if (token == 0)
			break ;
		cmd_tree->token = token;
		cmd_tree->cmd[i] = ft_strdup(non_token);
		if (!cmd_tree)
		{
			free_memory(s);
			free (non_token);
			return (NULL);
		}
		parse_line(cmd_tree->cmd[i]);
		cmd_tree->cmd[i] = check_quotes(cmd_tree->cmd[i]);
		i++;
		cmd_tree = parse_for_redirections(cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	return (cmd_tree);
}

t_cmd	*parse_exec_cmds(char **s)
{
	t_cmd	*cmd_tree;
	char	*non_token;

	non_token = NULL;
	cmd_tree = ft_init_struct();
	if (!cmd_tree)
		return (NULL);
	cmd_tree = parse_for_redirections(cmd_tree, s);
	if (!cmd_tree)
		return (NULL);
	cmd_tree = init_exec_cmds(cmd_tree, s, non_token);
	if (!cmd_tree)
		ft_free_cmd_struct(cmd_tree);
	return (cmd_tree);
}
