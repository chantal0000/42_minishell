/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/24 19:21:12 by kbolon           ###   ########.fr       */
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

t_exec	*init_exec_cmds(t_exec *exec, t_cmd *cmd, char **s, char *non_token)
{
	int		i;
	int		token;

	i = 0;
	if (!exec)
		return (NULL);
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		printf("\ntoken in init exec: %c\n", token);
		if (token == 0)//if not a token, break
			break ;
		exec->cmd[i] = ft_strdup(non_token);
		parse_line(exec->cmd[i]);
		i++;
		cmd = parse_for_redirections(cmd, s);
	}
	exec->cmd[i] = NULL;
	printf("cmds in exec:\n");//remove
	for (int i = 0; exec->cmd[i] != NULL; i++)//remove
		printf("cmd[%d]: %s\n", i, exec->cmd[i]);//remove
	return (exec);
}

t_cmd	*parse_exec_cmds(char **s, int *i)
{
	t_exec	*exec;
	t_cmd	*cmd;
	char	*non_token;

	non_token = NULL;
	printf("now in parse exec\n");
	if (check_next_char(s, '('))
	{
		printf("\nGROUP FOUND\n");
		cmd = parse_for_groups(s, i);
		return (cmd);
	}
	if (check_next_char(s, '\'') || check_next_char(s, '"'))
	{
		printf("\nQUOTES FOUND\n");
//		cmd = parse_for_quotes(s);
//		return (cmd);
	}
	cmd = init_exec();
	if(!cmd)
	{
		printf("cmd exec didn't initialise");
		exit (1);
	}
	(*i)++;
	cmd->index = *i;
	exec = (t_exec *)cmd;
	cmd = parse_for_redirections(cmd, s);
	exec = init_exec_cmds(exec, cmd, s, non_token);
//	printf("EXIT exec\n");
	return ((t_cmd *)exec);
}
