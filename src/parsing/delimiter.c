/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:21 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/14 14:34:29 by kbolon           ###   ########.fr       */
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

/*char	*check_quotes(char *s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[0] == s[len - 1])
		{
			temp = (char *)ft_calloc(len - 1, sizeof(char));
			if (!temp)
				return (NULL);
			while (i < len - 2)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
			ft_strcpy(s, temp);
			free (temp);
		}
	}
	return (s);
}*/

/*void	check_quotes(char *s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			temp = (char *)ft_calloc(len, sizeof(char));
			if (!temp)
				return ;
			while (i < len - 2)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
		}
	}
	s = temp;
	free (temp);
}*/

/*void	check_echo_and_quotes(t_cmd *cmd)
{}*/

void	check_quotes_single(char *s)
{
	size_t	i;
	size_t	len;
	size_t	new_len;
	char	*temp;

	len = ft_strlen(s);
	if (!s || len < 2)
		return ;
	i = 0;
	new_len = 0;
	if ((s[0] == '\'' && s[len - 1] == '\''))
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
			free(temp);
		}
	}
}

void	check_quotes_double(char *s)
{
	size_t	i;
	size_t	len;
	size_t	new_len;
	char	*temp;

	len = ft_strlen(s);
	if (!s || len < 2)
		return ;
	i = 0;
	new_len = 0;
	if ((s[0] == '\"' && s[len - 1] == '\"'))
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
void	check_quotes(char *s)
{
	check_quotes_double(s);
	check_quotes_single(s);
}