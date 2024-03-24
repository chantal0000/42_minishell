/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:22:50 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/24 10:09:32 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_head	*init_head(char **envp)
{
	t_head	*head;

	head = NULL;
	head = (t_head *)ft_calloc(1, sizeof(t_head));
	if (!head)
	{
		printf("calloc failed init list\n");//update per bash
		exit (1);
	}
	head->cmd_env = envp;
	head->cmd = NULL;
	printf("head initialized\n");//delete
	return (head);
}

t_cmd	*init_pipe(t_cmd *prev, t_cmd *next)
{
	t_cmd	*cmd;

	printf("\nnow initializing\n");//delete
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = PIPE;
	cmd->prev = prev;
	cmd->next = next;
	printf("cmd struct initialized\n\n");//delete
	return (cmd);
}

t_cmd	*init_exec()
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->type = EXEC;
	return ((t_cmd *)exec);
}


t_cmd	*init_redir(t_cmd *cmd_tree, char *file_name, int instructions, int fd)
{
	t_redir	*redir;

	if (!cmd_tree)
		return (NULL);
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->cmd = cmd_tree;
	redir->file_name = file_name;
	redir->instructions = instructions;
	if (fd == 0)
		redir->fd_in = fd;
	else if (fd == 1)
		redir->fd_out = fd;
	return ((t_cmd *)redir);
}
