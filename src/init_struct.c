/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/20 16:27:45 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_init_struct(t_cmd **cmd_tree)
{
	t_cmd	*temp;
	t_cmd	*ptr;

	temp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!temp)
		return (NULL);
	temp->prev = NULL;
	temp->next = NULL;
	temp->file_name = NULL;
	if (*cmd_tree == (void *)0)
		*cmd_tree = temp;
	else
	{
		ptr = *cmd_tree;
		while (ptr->next != NULL)
		{
			ptr->prev = ptr;
			ptr = ptr->next;
		}
		ptr->next = temp;
		temp->prev = ptr;
	}
	return (temp);
}
