/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:06:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/10 14:56:18 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** cd with only a relative or absolute path

** change directory, used to change current directory
** chdir function changes directories
** if it has more than 2 arguments it does not work
** cd without anything goes home (find home in env)
*/

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_cd(t_cmd *cmd)
{
	char	**cd_cmd;
	char	*home_dir;
	int		array_size;

	cd_cmd = cmd->cmd;
	array_size = ft_array_size(cd_cmd);
	if (array_size > 2)
		return (ft_handle_error_cd(cmd));
	home_dir = getenv("HOME");
	if (array_size == 1)
	{
		if (home_dir)
			chdir(home_dir);
	}
	else
	{
		if (cd_cmd[1])
		{
			if (chdir(cd_cmd[1]) != 0)
				return (ft_handle_error_cd(cmd));
		}
	}
	return (0);
}
