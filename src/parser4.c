/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:46:54 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/10 10:49:00 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//iterates through exec cmds and nulterminates cmd options
t_exec	*ft_exec_cmd(t_cmd *cmd)
{
	t_exec	*exec_cmd;
	int		i;

	if (!cmd)
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