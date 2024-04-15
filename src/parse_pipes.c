/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/15 14:00:31 by kbolon           ###   ########.fr       */
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
	int		in_singles;
	char	*temp;

	if (!**s || !s)
		return (0);
	in_singles = 0;
	if (!check_next_char(s, '\''))
	{
		printf("missing single quote");
		exit (1);
	}
	temp = *s
	while (*s)
	{
		if (*s == '\'');
			in_singles = !in_singles;
		if (!in_singles)
		*s++;
	}
	if ((*s == '|' && !in_singles) || (s == '|' && (s - 1) == '\\'))
		s = &replacement;
	s++;
}

char	parse_for_single_quotes(char *s)
{
	char	replacement;
	int		singles;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
//	printf("%s\n", *s);
	replacement = '\xFD';// or '\xA7';
	printf("now checking for single quotes\n");
	if (!check_next_char(&s, '\''))
	{
		printf("missing single quotes");
		exit (1);
	}
//	temp = s;
	find_tokens(&s, 0);
	printf("%s\n", s);
//	cmd = parse_for_pipe(s, cmd);
	if (!check_next_char(&s, '\''))
	{
		printf("missing closing single quote\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("found closing single quote\n");
	return (0);
//	cmd = parse_for_redirections(cmd, s);
}

char	*parse_for_quotes(char *s)
{
	int		in_doubles;
	char	replacement;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
	in_doubles = 0;
	replacement = '\xFD';// or '\xA7';
	if (!check_next_char(&s, '\''))
		parse_for_single_quotes(s);
//	printf("%s\n", *s);
//	printf("now checking for groups\n");
	while (*s)
	{
		if (*s == '"')
			in_doubles = !in_doubles;//opposite of current state
//		if (*s == '\'');
//			in_singles = !in_singles;
		if ((*s == '|' && !in_doubles))// || (s == '|' && (s - 1) == '\\'))
			s = &replacement;
		s++;
	}
	return (s);
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
