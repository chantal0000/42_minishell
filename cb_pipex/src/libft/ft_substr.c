/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:32:55 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/19 16:02:36 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			size;
	unsigned int	s_len;
	char			*substring;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
/*
#include <stdio.h>
int main(void)
{
	char *original = "Hello World! This is a long sentence.";
	unsigned int start = 0;
	size_t len = 5;

	char *substring = ft_substr(original, start, len);

	printf("original: %s \n", original);
	printf("substring: %s \n", substring);

	return (0);
} */
