/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:30 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/11 11:28:08 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//if (s != '\0' means we have stopped before end of string
void	parse_for_cmds(t_cmd **cmd, char *s)
{
	int		index;

	if (!s)
		return ;
	index = 0;
	s = check_for_quotes(s);
	parse_for_pipe(&s, cmd, 0, &index);
	parse_for_cat(*cmd);
	update_fd(*cmd);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	restore_pipes_and_spaces(*cmd);
	if (*s != '\0')
		error_message("check syntax", 1, 0);
}


char	*check_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;

	if (!s)
		return (NULL);
	in_single = 0;
	in_double = 0;
	temp = s;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != temp[-1] && (*temp - 1) != '\\' \
			&& !in_double)
			in_single = !in_single;
		else if (*temp == '\"' && (*temp - 1) != temp[-1] && \
			(*temp - 1) != '\\' && !in_single)
			in_double = !in_double;
		else if ((*temp == '|' || *temp == ' ' || *temp == '<' || \
			*temp == '>') && (in_single || in_double))
			ft_replace(temp);
		temp++;
	}
	if (in_single || in_double)
		error_message("open quotes found, can't parse", 1, 0);
	return (s);
}

char	ft_replace(char *c)
{
	if (*c == '|')
		*c = '\xFD';
	else if (*c == ' ')
		*c = '\xFE';
	else if (*c == '<')
		*c = '\xD1';
	else if (*c == '>')
		*c = '\xA8';
	return (*c);
}