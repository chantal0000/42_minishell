/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/10 12:23:52 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			error_message("parse exec failed", 1, 0);
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

void	restore_pipes_and_spaces(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	if (!cmd)
		return ;
	temp = cmd;
	while (temp)
	{
		while (temp->cmd[i])
		{
			ft_restore(temp->cmd[i]);
			i++;
		}
		temp = temp->next;
	}
}

void	ft_restore(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (*s == '\xFD')
			*s = '|';
		if (*s == '\xFE')
			*s = ' ';
		if (*s == '\xD1')
			*s = '<';
		if (*s == '\xA8')
			*s = '>';
		s++;
	}
}
