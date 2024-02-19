/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:59:32 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/22 12:48:43 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_find_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	return (start);
}

size_t	ft_find_end(char const *s1, size_t start, char const *set)
{
	size_t	end;

	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		end--;
	return (end);
}

char	*ft_empty_str(void)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * 1);
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	return (new_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	start;
	size_t	end;
	size_t	trim_len;
	size_t	i;

	start = ft_find_start(s1, set);
	end = ft_strlen(s1) - 1;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (start == end + 1)
		return (ft_empty_str());
	end = ft_find_end(s1, start, set);
	trim_len = end - start + 1;
	new_str = (char *)malloc((trim_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < trim_len)
	{
		new_str[i] = s1[start + i];
		i++;
	}
	new_str[trim_len] = '\0';
	return (new_str);
}
