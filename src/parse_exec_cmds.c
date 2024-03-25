/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/25 14:50:45 by kbolon           ###   ########.fr       */
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

void	init_exec_cmds(t_cmd *node, char **s, char *non_token, char **envp, int *i)
{
	int		j;
	int		token;

	printf("filling cmd array in list\n");
	j = 0;
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		printf("\ntoken in init exec: %c\n", token);
		if (token == 0)//if not a token, break
			break ;
		if (!node->cmd)
		{
			node->cmd = (char **)ft_calloc((MAXARGS + 1), sizeof(char *));
			if (!node->cmd)
			{
				printf("array not initialised\n");
				exit (1);
			}
		}
		printf("array initialized\n");
		node->cmd[j] = ft_strdup(non_token);
		if (!node->cmd[j])
		{
			printf("problems with copying line in array\n");
			exit (1);
		}
		parse_line(node->cmd[j]);
		j++;
		node = parse_for_redirections(node, s, i, envp);//need to add envp?
	}
	node->cmd[j] = NULL;
	printf("cmds in exec:\n");//remove
	for (int i = 0; node->cmd[i] != NULL; i++)//remove
		printf("cmd[%d]: %s\n", i, node->cmd[i]);//remove
}

t_cmd	*parse_exec_cmds(char **s, int *i, char **envp)
{
	t_cmd	*node;
	char	*non_token;

	non_token = NULL;
//	node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	node = build_cmd_tree(cmd, temp, i, envp);
	if (!node)
	{
		printf("node not initialised 1\n");
		exit (1);
	}
	printf("in parse for exec\n");
	if (check_next_char(s, '('))
	{
		printf("\nGROUP FOUND\n");
		node = parse_for_groups(s, i, envp);
		return (node);
	}
	if (check_next_char(s, '\'') || check_next_char(s, '"'))
	{
		printf("\nQUOTES FOUND\n");
//		node = parse_for_quotes(s);
//		return (node);
	}
//	node->index = *i;
	node = parse_for_redirections(node, s, i, envp);//need to add envp?
	init_exec_cmds(node, s, non_token, envp, i);
	if (!node->cmd[0])
	{
		printf("cmd exec didn't initialise");
		exit (1);
	}
	return (node);
}
