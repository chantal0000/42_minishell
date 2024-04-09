/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/09 17:20:56 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cmd is prev subtree and temp next subtree and if more pipes, 
//will create a new pipe node
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, int *index)
{
	t_cmd	*temp;
	t_cmd	*temp2;

	temp2 = NULL;
	if (!**str || !str)
		return ;
	if (prev_pipe == 0)
	{
		temp = parse_exec_cmds(str);
		if (!temp)
			return ;
		temp->index = *index;
		m_lstadd_back(cmd, temp);
	}
	(*index)++;
	if (check_next_char(str, '|'))
	{
		find_tokens(str, NULL);
		temp2 = parse_exec_cmds(str);
		temp2->index = *index;
		m_lstadd_back(cmd, temp2);
		parse_for_pipe(str, cmd, 1, index);
	}
}

/*t_cmd	*parse_for_single(char **s)
{
	t_cmd	*cmd;

	if (!**s || !s)
		return (0);
	if (!check_next_char(s, '\''))
	{
		printf("missing prev bracket");
		exit (1);
	}
}
void	*parse_for_quotes(char *s)
{
	int		in_doubles;
	int		in_singles;
	char	replacement;
//	t_exec	cmd;
//	int		token;

	if (!*s || !s)
	{
		printf("string is empty");
		exit(1);
	}
	in_quotes = 0;
	in_singles = 0;
	replacement = \xFD;// or '\xA7';
//	printf("%s\n", *s);
//	printf("now checking for groups\n");
	while (*s)
	{
		if (*s == '"')
			in_doubles = !in_doubles;//opposite of current state
		if (*s == '\'');
			in_singles = !in_singles;
		if (in_doubles)
		if ((*s == '|' && !in_doubles) || (*s == '|' && *(s - 1) == '\\'))
			*s = replacement;
		*s++;
	}
}
void	restore_pipes(char *s)
{
	if (!*s || !s)
		return ;
	while (*s)
	{
		if (*s == '\xFD')
			*s = '|';
		*s++;
	}
}*/
