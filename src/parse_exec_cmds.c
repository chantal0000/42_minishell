/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/08 18:06:51 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/*t_cmd	*init_exec_cmds(char **s, char *non_token)
{
	int		i;
	int		token;
	t_cmd	*cmd_tree;

	i = 0;
	token = 0;
//	cmd_tree = ft_init_stuct();
//	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
	{
		free(non_token);
		return (NULL);
	}
//	cmd_tree = parse_for_redirections(cmd_tree, s);//check for redirs and pass the tree we have built so far
	if (!cmd_tree)
	{
		free(non_token);
		return (NULL);
	}
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		if (token == 0)
			break ;
		cmd_tree->cmd[i] = ft_strdup(non_token);
		if (!cmd_tree->cmd[i])
		{
			free_memory(s);
			free(non_token);
			free_cmd(cmd_tree);
			exit (1);
		}
		parse_line(cmd_tree->cmd[i]);
		i++;
//		cmd_tree = parse_for_redirections(cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	return (cmd_tree);
}

t_cmd	*parse_exec_cmds(char **s)
{
	t_cmd	*cmd_tree;
	char	*non_token;
	int		i;

	non_token = NULL;
	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
	{
		free (non_token);
		printf("cmd_tree initiation in exec failed\n");
		exit (1);
	}
	i = 0;
	while (i < MAXARGS)
	{
		cmd_tree->cmd[i] = NULL;
		i++;
	}
	cmd_tree = init_exec_cmds(s, non_token);
	if(!cmd_tree)
	{
		free (non_token);
		exit (1);
	}
	return (cmd_tree);
}*/
t_cmd	*init_exec_cmds(char **s, char *non_token)
{
	int		i;
	int		token;
	t_cmd	*cmd_tree;

	i = 0;
	token = 0;
	cmd_tree = ft_init_stuct();
	if (!cmd_tree)
	{
		free(non_token);
		return (NULL);
	}
	cmd_tree = parse_for_redirections(cmd_tree, s);
	if (!cmd_tree)
	{
		free(non_token);
		return (NULL);
	}
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		if (token == 0)
			break ;
		cmd_tree->cmd[i] = ft_strdup(non_token);
		if (!cmd_tree->cmd[i])
		{
			free_memory(s);
			free(non_token);
			free_cmd(cmd_tree);
			exit (1);
		}
		parse_line(cmd_tree->cmd[i]);
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
	int		i;

	non_token = NULL;
	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
	{
		printf("cmd_tree initiation in exec failed\n");
		exit (1);
	}
	i = 0;
	while (i < MAXARGS)
	{
		cmd_tree->cmd[i] = NULL;
		i++;
	}
	cmd_tree = init_exec_cmds(s, non_token);
	if(!cmd_tree)
	{
		exit (1);
	}
	return (cmd_tree);
}