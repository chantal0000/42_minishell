/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/27 15:27:58 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_line(char *arr)
{
	int	i;

	i = 0;
	while (arr[i] != '\0' && (!is_whitespace(arr[i]) && !is_token(arr[i])))
		i++;
	arr[i] = '\0';
	return (arr);
}

/*char	**init_cmd_to_exec()
{
	char	**exec;

	exec = (char **)ft_calloc(1, MAXARGS);
	if (!exec)
		return (NULL);
//	exec->type = EXEC;
	return (exec);
}*/

t_cmd	*init_exec_cmds(char **s, char *non_token)
{
	int		i;
	int		token;
	t_cmd	*cmd_tree;

	i = 0;
	token = 0;
	cmd_tree = ft_init_stuct();
	cmd_tree = parse_for_redirections(cmd_tree, s);//check for redirs and pass the tree we have built so far
	if (!cmd_tree)
		return (NULL);
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		if (token == 0)//if not a token, break
			break ;
		cmd_tree->cmd[i] = ft_strdup(non_token); 
		parse_line(cmd_tree->cmd[i]);
		i++;
		cmd_tree = parse_for_redirections(cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
/*	for (int i = 0; cmd_tree->cmd[i] != NULL; i++)
		printf("cmd[%d]: %s\n", i, cmd_tree->cmd[i]);*/
	return (cmd_tree);
}

t_cmd	*parse_exec_cmds(char **s)
{
	t_cmd	*cmd_tree;
	char	*non_token;
	int		i;

	non_token = NULL;
	cmd_tree = (t_cmd *)calloc(1, sizeof(t_cmd));
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
//	printf("now in parse exec\n");
	/*if (check_next_char(s, '('))
	{
		printf("\nGROUP FOUND\n\n");
		cmd_tree = parse_for_groups(s);
		return (cmd_tree);
	}*/
	cmd_tree = init_exec_cmds(s, non_token);//fill the struct
	if(!cmd_tree)
		free (cmd_tree);
	for (int i = 0; cmd_tree->cmd[i] != NULL; i++)
		printf("cmd[%d]: %s\n", i, cmd_tree->cmd[i]);
//	printf("EXIT exec\n");
	return (cmd_tree);
}