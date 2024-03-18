/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_and_groups.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/18 14:31:43 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cmd is prev subtree and temp next subtree and if more pipes, 
//will create a new pipe node
t_cmd	*parse_for_pipe(char **str)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (!**str || !str)
		return (0);
	printf("now parsing for pipes\n");
	printf("string in pipe: %s\n", *str);
	cmd = ft_init_stuct();
	if (!cmd)
		return (NULL);
	temp = parse_exec_cmds(str);
	if (!temp)
		return (NULL);
	if (check_next_char(str, '|'))
	{
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL);
		cmd->type = PIPE;
		cmd->prev = temp;
		cmd->next = parse_for_pipe(str);
		return (cmd);
	}
	printf("\nEXIT PIPE PARSING FCN\n");
	return (temp);
}

t_cmd	*parse_for_groups(char **s)
{
	t_cmd	*cmd;
//	int		token;

	if (!**s || !s)
		return (0);
	printf("%s\n", *s);
	printf("now checking for groups\n");
	if (!check_next_char(s, '('))
	{
		printf("missing prev bracket");
		exit (1);
	}
	find_tokens(s, 0);
	printf("%s\n", *s);
	cmd = parse_for_pipe(s);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("found closing bracket\n");
	printf("\nGROUP CLOSED\n");
	cmd = parse_for_redirections(cmd, s);
	return (cmd);
}
