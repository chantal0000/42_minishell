/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/26 18:11:31 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_cmd	*ft_init_stuct(void)
{
	t_cmd	*cmd_tree;

	cmd_tree = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_tree)
		return (NULL);
	return (cmd_tree);
}

/*t_cmd	*ft_init_struct(t_env *env)
{
	t_cmd	*cmd_tree;
	int		i;

	i = 0;
	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
		return (NULL);
	printf("first node initialised\n");
	cmd_tree->index = 0;
	cmd_tree->prev = NULL;
	cmd_tree->next = NULL;
	cmd_tree->m_env = env;
	while (i < MAXARGS)
	{
		cmd_tree->cmd[i] = NULL;
		i++;
	}
	return (cmd_tree);
}*/

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

t_cmd	*add_cmd(t_cmd *prev, t_cmd *next, int *i)
{
	t_cmd	*list;

	list = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!list)
	{
		printf("ft_calloc failed adding another cmd to the cmd tree\n");//update per bash
		exit (1);
	}
	list->index = *i;
	list->prev = prev;
	list->next = next;
	list->fd_in = -1;
	list->fd_out = -1;
	printf("cmd[%d] added to the cmd tree\n", *i);//delete
	(*i)++;
	return (list);
}*/

t_cmd	*add_node(t_cmd *cmd, t_cmd *next, t_env *env, int index)
{
	t_cmd	*temp;
	t_cmd	*ptr;
	int		i;

	i = 0;
	printf("\nnow adding new node\n");
	temp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!temp)
		return (NULL);
	temp->m_env = env;
	while (i < MAXARGS)
	{
		temp->cmd[i] = NULL;
		i++;
	}
	ptr = cmd;
	while (ptr->next != NULL)
	{
		ptr->prev = ptr;
		ptr = ptr->next;
	}
	ptr->next = temp;
	temp->prev = ptr;
	temp->next = next;
	temp->index = index;
	return (temp);
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
