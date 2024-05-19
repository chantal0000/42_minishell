/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 10:46:26 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//cmd is prev subtree and temp next subtree and if more pipes, 
//will create a new pipe node
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe)
{
	t_cmd	*temp;

	if (!**str || !str)
		return ;
	if (prev_pipe == 0)
	{
		temp = parse_exec_cmds(str);
		if (!temp)
		{
			ft_free_cmd_struct(*cmd);
			error_general("parse exec failed");
		}
		m_lstadd_back(cmd, temp);
	}
	if (check_next_char(str, '|'))
		pipe_found_fcn(cmd, str);
}

void	pipe_found_fcn(t_cmd **cmd, char **str)
{
	t_cmd	*temp;

	find_tokens(str, NULL);
	temp = parse_exec_cmds(str);
	if (!temp)
	{
		ft_free_cmd_struct(*cmd);
		error_general("parse exec failed");
	}
	m_lstadd_back(cmd, temp);
	parse_for_pipe(str, cmd, 1);
}

void	restore_pipes_and_spaces(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	if (!cmd)
		return ;
	temp = cmd;
	while (temp)
	{
		i = 0;
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
			*(s) = '|';
		else if (*s == '\xFE')
			*(s) = ' ';
		else if (*s == '\xD1')
			*(s) = '<';
		else if (*s == '\xA8')
			*(s) = '>';
		else if (*s == '\xAC')
			*(s) = '$';
		s++;
	}
}
