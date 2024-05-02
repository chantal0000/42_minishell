/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/02 15:02:07 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_echo(t_cmd *cmd)
{
	t_cmd	*temp;
	int		num;
	int		i;

	temp = cmd;
	num = ft_count(temp->cmd);
	if (temp->token == 'n')
		i = 2;
	if (temp->token == 'e')
		i = 1;
	while (i < num)
	{
		if (i == num - 1)
			printf("%s", check_quotes(temp->cmd[i]));
		else
			printf("%s ", temp->cmd[i]);
		i++;
	}
	if (cmd->token == 'e')
		printf("\n");
}


