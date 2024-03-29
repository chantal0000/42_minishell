/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/29 21:38:21 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_init_stuct(void)
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
	while (temp->next != NULL)
	{
		if (temp->file_name == NULL)
		{
			tree->fd_in = -1;
			tree->fd_out = -1;
		}
		temp = temp->next;
	}
	tree = temp;
}
