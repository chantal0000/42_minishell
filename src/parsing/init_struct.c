/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/30 16:45:14 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_init_struct(void)
{
	t_cmd	*cmd_tree;

	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
		return (NULL);
	return (cmd_tree);
}

t_cmd	*m_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst -> next;
	return (lst);
}

void	m_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		new->prev = m_lstlast(*lst);
		new->next = NULL;
		m_lstlast(*lst)->next = new;
	}
	else
	{
		new->next = NULL;
		new->prev = NULL;
		*lst = new;
	}
}

void	update_fd(t_cmd *tree)
{
	t_cmd	*temp;

	if (!tree)
		return ;
	temp = tree;
	while (temp)
	{
		if (temp->file_name == NULL)
		{
			temp->fd_in = -1;
			temp->fd_out = -1;
		}
		temp->pid = 0;
		if (ft_strcmp(temp->cmd[0], "echo") == 0)
		{
			if (ft_strcmp(temp->cmd[1], "-n") == 0)
				temp->token = 'n';
			else
				temp->token = 'e';
		}
		temp = temp->next;
	}
	tree = temp;
}

void	parse_for_echo(t_cmd *cmd_tree)
{
	t_cmd	*temp;

	temp = cmd_tree;
	while (temp)
	{
		if (!ft_strcmp(temp->cmd[0], "echo") && !ft_strcmp(temp->cmd[1], "-n"))
			temp->token = 'n';
		else if (!ft_strcmp(temp->cmd[0], "echo") && ft_strcmp(temp->cmd[1], "-n"))
			temp->token = 'e';
		else
			temp = temp->next;
	}
//	cmd_tree = temp;
}

t_exp	*insert_exp(t_exp *head, char *name, char *value)
{
	t_exp	*new_node;
	t_exp	*temp;

	new_node = (t_exp *)ft_calloc(1, sizeof(t_exp));
	if (!new_node)
		return (NULL);
	new_node->exp_name = ft_strdup(name);
/*	if (!new_node->exp_name)
	{
		free (new_node);
		return (NULL);
	}*/
	new_node->exp_value = ft_strdup(value);
/*	if (!new_node->exp_value)
	{
		free (new_node);
		return (NULL);
	}*/
	new_node->next = NULL;
	if(!head)
		return (new_node);
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (head);
}
