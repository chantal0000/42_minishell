/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/25 14:09:41 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*init_cmd(t_cmd *next, char **envp, int *i)
{
	t_cmd	*head;

	head = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!head)
	{
		printf("calloc failed init list\n");//update per bash
		exit (1);
	}
	head->type = EXEC;
	head->index = *i;
	head->env = envp;
	head->prev = NULL;
	head->next = next;
	head->fd_in = -1;
	head->fd_out = -1;
	printf("first cmd[%d] initialized\n", *i);//delete
	(*i)++;
	return (head);
}

t_cmd	*add_cmd(t_cmd *prev, t_cmd *next, int *i, char **envp)
{
	t_cmd	*list;

	list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!list)
	{
		printf("calloc failed adding another cmd to the cmd tree\n");//update per bash
		exit (1);
	}
	list->type = EXEC;
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
	if (!cmd_node)
		return (NULL);
	if (prev == NULL)
	{
		cmd_node = init_cmd(next, envp, i);
		if (!cmd_node)
			return (NULL);
		return (cmd_node);
	}
	if (prev)
	{
		cmd_node = add_cmd(prev, next, i, envp);
		if (!cmd_node)
			return (NULL);
		return (cmd_node);
	}
	return (cmd_node);
}

/*t_cmd	*init_exec()
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->type = EXEC;
	return ((t_cmd *)exec);
}*/


t_cmd	*init_redir(t_cmd *cmd_tree, char *file_name, int instructions, int fd)
{
	t_cmd	*redir;

	if (!cmd_tree)
		return (NULL);
	redir = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
//	redir->cmd = cmd_tree;
	redir->file_name = file_name;
	redir->instructions = instructions;
	if (fd == 0)
		redir->fd_in = fd;
	else if (fd == 1)
		redir->fd_out = fd;
	return ((t_cmd *)redir);
}
