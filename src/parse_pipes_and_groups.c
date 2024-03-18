/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_and_groups.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/18 16:59:12 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cmd is prev subtree and temp next subtree and if more pipes, 
//will create a new pipe node
t_cmd	*parse_for_pipe(char **str)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	int		token;

	if (!**str || !str)
		return (0);
	token = 0;
	printf("now parsing for pipes\n");
	printf("string in pipe: %s\n", *str);
	cmd = parse_exec_cmds(str);
	if (!cmd)
		return (NULL);
//	token = find_tokens(str, NULL);
	printf("string in pipe after exec fcn: %s\n", *str);
	
	token = check_next_char(str, '|');
	printf("\ntoken in pipe fcn %c\n\n", token);
//	printf("\nnext char in pipe fcn %d\n\n", token);
//	if (check_next_char(str, '|'))
	if (token == 1)
	{
		temp = ft_init_stuct();
		if (!temp)
			return (NULL);
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL);
		temp->type = PIPE;
		temp->prev = cmd;
		temp->next = parse_for_pipe(str);
		return (temp);
	}
	else
		return (cmd);
}

t_cmd	*parse_for_groups(char **s)
{
	t_cmd	*cmd;
	int		token;

	if (!**s || !s)
		return (0);
	printf("%s\n", *s);
	printf("now checking for groups\n");
	if (!check_next_char(s, '('))
	{
		printf("missing prev bracket");
		exit (1);
	}
	token = find_tokens(s, 0);
	printf("string in group %s\n", *s);
	printf("token in group %c\n", token);
	cmd = parse_for_pipe(s);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("\nGROUP CLOSED\n");
	find_tokens(s, 0);
	cmd = parse_for_redirections(cmd, s);
	return (cmd);
}
