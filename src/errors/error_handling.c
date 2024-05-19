/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:14:08 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 17:08:11 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_temp(char *str, char *temp)
{
	perror(str);
	unlink(temp);
	return ;
}

void	error_general(char *str)
{
	perror(str);
	return ;
}
