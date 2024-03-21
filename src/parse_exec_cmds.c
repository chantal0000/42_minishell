/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/20 16:59:53 by kbolon           ###   ########.fr       */
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

t_cmd	*init_exec_cmds(t_cmd *tree, char **s, char *non_token)
{
	int		i;
	int		token;
//	t_cmd	*cmd_tree;

	i = 0;
	token = 0;
//	cmd_tree = parse_for_redirections(cmd_tree, s);//check for redirs and pass the tree we have built so far
	tree = parse_for_redirections(tree, s);
	if (!tree)
		return (NULL);
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
//		printf("token in init exec: %c\n", token);
		if (token == 0)//if not a token, break
			break ;
		tree->cmd[i] = ft_strdup(non_token);
		parse_line(tree->cmd[i]);
		i++;
		tree = parse_for_redirections(tree, s);
	}
	tree->cmd[i] = NULL;
	printf("cmds in exec:\n");//remove
	for (int i = 0; tree->cmd[i] != NULL; i++)//remove
		printf("cmd[%d]: %s\n", i, tree->cmd[i]);//remove
	return (tree);
}

t_cmd	*parse_exec_cmds(t_cmd *tree, char **s)
{
//	t_cmd	*cmd_tree;
	char	*non_token;

	non_token = NULL;
//	printf("now in parse exec\n");
	if (check_next_char(s, '('))
	{
		printf("\nGROUP FOUND\n");
		tree = parse_for_groups(s);
		return (tree);
	}
	tree = init_exec_cmds(tree, s, non_token);//fill the struct
	if(!tree)
		free (tree);
//	printf("EXIT exec\n");
	return (tree);
}
