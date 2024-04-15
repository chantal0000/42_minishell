/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/15 13:50:39 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	char	quote;
	int		i;
	char	*s;

	i = 0;
	s = cmd->cmd[1];
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)//use ft_strncmp
	{
		while (s[i] != '\0')
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				quote = s[i];
				i++;
			}
			while (s[i] != '\0' && s[i] != quote)
			{
				write (1, &s[i], 1);
				i++;
			}
			if (s[i] == quote) 
				i++;
			else
			{
				write (1, &s[i], 1);
				i++;
			}
		}
	}
}
