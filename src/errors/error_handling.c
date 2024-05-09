/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:14:08 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/09 10:40:03 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_message(char *str, int i, int fd)
{
	if (fd)
		close (fd);
	perror(str);
	exit (i);
}
void	error_temp(char *str, char *temp)
{
		perror(str);
		unlink(temp);
		return;
}

void	error_general(char *str)
{
	perror(str);
	return ;
}