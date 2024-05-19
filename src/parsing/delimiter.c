/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:21 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/19 10:58:24 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_delimiter(char *s1, char *delim)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && delim[j] != '\0' && s1[i] == delim[j])
	{
		i++;
		j++;
	}
	if (delim[j] == '\0')
		return (1);
	return (0);
}


void	check_quotes(char *s)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (!s || len < 2)
		return ;
	i = 0;
	quote_helper(s, '\'', i, len);
	quote_helper(s, '\"', i , len);
}

void	quote_helper(char *s, int quote, size_t i, size_t len)
{
	size_t	new_len;
	char	*temp;

	new_len = 0;
	if ((s[0] == quote && s[len - 1] == quote))
	{
		if (s[i] == s[len - 1])
		{
			new_len = len - 2;
			temp = (char *)ft_calloc(new_len + 1, sizeof(char));
			if (!temp)
				return ;
			while (i < new_len)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
			ft_strcpy(s, temp);
			ft_restore(s);
			free(temp);
		}
	}
}
