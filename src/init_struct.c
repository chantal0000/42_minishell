/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/25 19:05:21 by kbolon           ###   ########.fr       */
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

/*t_cmd	*init_cmd(char **envp)
{
	t_cmd	*temp;

	printf("insert cmd\n");
	temp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!temp)
	{
		printf("calloc failed init list\n");//update per bash
		exit (1);
	}
	temp->env = envp;
	temp->prev = NULL;
	temp->next = NULL;
	printf("finished insert 1\n");
	return (temp);
}

t_cmd	*add_cmd(t_cmd *prev, t_cmd *next, int *i, char **envp)
{
	t_cmd	*list;

	list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!list)
	{
		printf("ft_calloc failed adding another cmd to the cmd tree\n");//update per bash
		exit (1);
	}
	list->index = *i;
	list->env = envp;
	list->prev = prev;
	list->next = next;
	list->fd_in = -1;
	list->fd_out = -1;
	printf("cmd[%d] added to the cmd tree\n", *i);//delete
	(*i)++;
	return (list);
}

t_cmd	*build_cmd_tree(t_cmd *prev, t_cmd *next, int *i, char **envp)
{
	t_cmd	*cmd_node;

	printf("\nnow initializing\n");//delete
	cmd_node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
 (!cmd_node)
		return (NULL);
	if (prev == NULL)
	{
		cmd_node = init_cmd(next, envp, i);
		if (!cmd_node)
			return (NULL);
		return (cmd_node);
	}
	if (cmd_node->next == NULL)
	{
		cmd_node = add_cmd(prev, next, i, envp);
		if (!cmd_node)
			return (NULL);
//		cmd_node->next = NULL;
		return (cmd_node);
	}
	return (cmd_node);
}*/

/*t_cmd	*init_exec()
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->type = EXEC;
	return ((t_cmd *)exec);
}*/

t_cmd	*redir_cmd(t_cmd *node, int instructions, int fd)
{
	if (!node)
		return (NULL);
	node->instructions = instructions;
	if (fd == 0)
		node->fd_in = fd;
	else if (fd == 1)
		node->fd_out = fd;
	return (node);
}
