/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nul_terminate_fcns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:46:54 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/18 11:48:06 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//When a struct cmd* is received, it points to a base struct w/ limited 
//fields. To manipulate extended fields in structures like t_exec or 
//t_redir, the pointer must be cast to the appropriate type. 
//This casting informs the compiler of the pointer's actual structure type, 
//enabling access to both base and extended fields.

//This approach facilitates polymorphism in C, enabling functions like 
//ft_nul_cmds to operate on various command types through a 
//common interface. By examining the type field and casting accordingly, 
//the function ensures type safety while handling diverse command structures.
/*t_cmd	*ft_nul_cmds(t_cmd *cmd)
{
	t_cmd	*pipe_cmd;
	t_cmd	*redir_cmd;

	if (!cmd)
		return (NULL);
	if (cmd->type == PIPE)
	{
		pipe_cmd = cmd;
		{
			ft_nul_cmds(pipe_cmd->prev);
			ft_nul_cmds(pipe_cmd->next);
		}
//		printf("nul terminated pipe\n");
	}
	if (cmd->type == REDIR)
	{
		redir_cmd = cmd;
		ft_nul_cmds(redir_cmd->cmd);
//		redir_cmd->end_file = 0;
//		printf("nul terminated redir\n");
	}
	return (cmd);
}*/


//iterates through exec cmds and nulterminates cmd options
/*t_exec	*ft_exec_cmd(t_cmd *cmd)
{
	t_exec	*exec_cmd;
	int		i;

	printf("now in ft_exec_cmd\n");
	if (!cmd)
		return (0);
	i = 0;
	exec_cmd = (t_exec *)cmd;
	while (exec_cmd->cmd[i] != NULL)
		i++;
	printf("end of cmd/opt: %s\n", exec_cmd->cmd[i]);
	printf("exit ft_exec_cmd\n");
	return (exec_cmd);
}*/

/*char	*ft_strtok(char *str, char *delimiter)
{
	static char	*ptr;
	char		*token;

	if (str != NULL)
		ptr = str;
	if (*ptr != '\0'  && ft_strchr(delimiter, *ptr))
		ptr++;
	if (*ptr == '\0')
		return (NULL); //return NULL if no more tokens
	token = ptr;
	while (*ptr != '\0' && !ft_strchr(delimiter, *ptr))//if char is a delimiter, it returns the token
		ptr++;
	if (*ptr != '\0')
		*ptr++ = '\0';
	return (token);
}*/