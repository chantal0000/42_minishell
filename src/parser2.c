/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:03 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/04 17:10:12 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_alligators(char *s)
{
	int	token;

	token = *(int *)s;
	if (*s == '>')
	{
		(*s)++;
		if (*s == '>')
		{
			token = '+';
			(*s)++;
		}
	}
	else if (*s == '<')
	{
		(*s)++;
		if (*s == '<')
		{
			token = '-';
			(*s)++;
		}
	}
	return (token);
}

int	find_tokens(char **s, char **cmd, char **opt)
{
	int		token;

	while (*s != (void *)0 && is_whitespace(*s))
		s++;
	if (cmd)
		(*cmd) = *s;
	token = *(int *)s;
	while (*s != (void *)0)
	{
		if (ft_strchr("|()", *(int *)s))
			s++;
		token = check_for_alligators(*s);
		if (token == 'a')
		{
			while (*s != (void *)0 && !is_whitespace(*s) && !is_token(*s))
				s++;
		}
	}
	if (opt)
		(*opt) = *s;
	while (*s != (void *)0 && is_whitespace(*s))
		s++;
	return (token);
}

//When a struct cmd* is received, it points to a base structure with limited fields. 
//To manipulate extended fields in derived structures like struct exec_cmd or 
//struct redir_cmd, the pointer must be cast to the appropriate type. 
//This casting informs the compiler of the pointer's actual structure type, 
//enabling access to both base and extended fields.

//This approach facilitates polymorphism in C, enabling functions like 
//nul_terminate_cmds to operate on various command types through a 
//common interface. By examining the type field and casting accordingly, 
//the function ensures type safety while handling diverse command structures.

t_cmd	*ft_nul_cmds(t_cmd *cmd)
{
	t_exec	*exec_cmd;
	t_cmd	*pipe_cmd;
	t_redir	*redir_cmd;
	int		i;

	if(!cmd)
		return (0);
	i = 0;
	if (cmd->type == EXEC)
	{
		exec_cmd = (t_exec *)cmd;
		while (exec_cmd->cmd[i])
		{
			exec_cmd->options[i] = 0;
			i++;
		}
	}
	if (cmd->type == PIPE)
	{
		pipe_cmd = (t_cmd *)cmd;
		{
			ft_nul_cmds(pipe_cmd->left);
			ft_nul_cmds(pipe_cmd->right);
		}
	}
	if (cmd->type == REDIR)
	{
		redir_cmd = (t_redir *)cmd;
		ft_nul_cmds(redir_cmd->cmd);
		redir_cmd->end_file = 0;
	}
	return (cmd);
}

t_cmd *pipe_cmd (t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (cmd);
}

//iterates through exec cmds and nulterminates cmd options
t_exec	*ft_exec_cmd(t_cmd *cmd)
{
	t_exec	*exec_cmd;
	int			i;

	if(!cmd)
		return (0);
	i = 0;
	exec_cmd = (t_exec *)cmd;
	while (exec_cmd->cmd[i])
	{
		*exec_cmd->options[i] = 0;
		i++;
	}
	return (exec_cmd);
}
