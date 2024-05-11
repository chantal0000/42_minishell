/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_cat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:17:57 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/11 15:24:32 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_for_cat(t_cmd *cmd)
{
	t_cmd	*temp;
	size_t	i;

	temp = cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			if (ft_strcmp(temp->cmd[i], "cat") == 0 && !temp->cmd[i + 1])
			{
				ft_catdoc(temp);
//				printf("cat | found\n");
//				break ;
			}
			i++;
		}
		temp = temp->next;
	}
}

void	ft_catdoc(t_cmd *cmd)
{
	static char	*str;

	str = readline(">");
	if (!str)
		error_general("minishell: warning: delimited by end-of-file");
	cmd->cmd[0] = ft_strdup(str);
	cmd->fd_out = -1;
//	printf("fd_in: %d\n", cmd->fd_in);
//	printf("fd_out: %d\n", cmd->fd_out);
	str = readline("");
	if (!str)
		error_general("minishell: warning: delimited by end-of-file");
	free (str);
}