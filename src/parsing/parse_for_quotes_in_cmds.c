/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_quotes_in_cmds.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:08:19 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/14 07:15:29 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_quotes(char *str)
{
	char	*src;
	char	*dst;
	
	src = str;
	dst = str;
	while (*src)
	{
		if (*src == '\'' || *src == '\"')
		{
			src++;
			continue ;
		}
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
//	return (dst);
}

void	check_in_cmd_array_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;

	if (!s)
		return ;
	in_single = 0;
	in_double = 0;
	temp = s;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != temp[-1] && (*temp - 1) != '\\' \
			&& !in_double)
			in_single++;
		else if (*temp == '\"' && (*temp - 1) != temp[-1] && \
			(*temp - 1) != '\\' && !in_single)
			in_double++;
		temp++;
	}
	if (in_single % 2 == 0 && in_double % 2 == 0)
		remove_quotes(s);
//	return (s);
}