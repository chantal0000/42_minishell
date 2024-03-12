/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 18:31:55 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_for_groups(char **s)
{
	t_cmd	*cmd;

	printf("now checking for groups\n");
	if (!check_next_char(s, '('))
	{
		printf("missing left bracket");
		exit (1);
	}
	find_tokens(s, NULL , NULL);
	cmd = parse_for_pipe(s);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("found closing bracket\n");
	printf("\nGROUP CLOSED\n");
//	cmd = parse_for_redirections(cmd, s);
	return (cmd);
}


t_cmd	*parse_exec(char **s, t_exec *cmd_tree, char *cmd, char *opt)
{
	int		i;
	int		token;

	i = 0;
	token = 0;
	printf("\nin parse_exec\n");
	while (!check_next_char(s, '|') || !check_next_char(s, ')'))
	{
		token = find_tokens(s, &cmd, &opt);
		if (!token)
			break ;
		if (token != 'a' && !is_token(token))
		{
			printf("please enter valid commands\n");
			return (NULL);
		}
		printf("cmd: %c\n", *cmd);
		printf("opt: %c\n", *opt);
		cmd_tree->cmd[i] = cmd; //pointer to token
		cmd_tree->options[i] = opt; //pointer to space after token
		i++;
		if (i > MAXARGS)
		{
			printf("too many args");
			exit (1);
		}
//		cmd_tree = (t_exec *)parse_for_redirections((t_cmd *)cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	cmd_tree->options[i] = NULL;
	return ((t_cmd *)cmd_tree);
}

t_cmd	*build_cmd_tree(char **s)
{
	t_cmd	*cmd_tree;
	char	*cmd;
	char	*opt;

	cmd = *s;
	opt = *s;
	printf("now building cmd tree\n");
	if (check_next_char(s, '('))
	{
		printf("\nGROUP FOUND\n\n");
		cmd_tree = parse_for_groups(s);
		return (cmd_tree);
	}	
	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
		return (NULL);
	cmd_tree->type = EXEC;
//	cmd_tree = parse_for_redirections(cmd_tree, s);
	cmd_tree = parse_exec(s, (t_exec *)cmd_tree, cmd, opt);
	if(!cmd_tree)
		free (cmd_tree);
	return (cmd_tree);
}
