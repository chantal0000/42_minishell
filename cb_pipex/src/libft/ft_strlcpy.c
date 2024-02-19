/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:47:42 by chbuerge          #+#    #+#             */
/*   Updated: 2024/01/15 16:19:54 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	if (size > 0)
	{
		while (src[len] && len < (size -1))
		{
			dest[len] = src[len];
			len++;
		}
		dest[len] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
/*
int main()
{
	char dest[20];
	const char *src = "Hello World";

	size_t size = 5;

	// size = ft_strlcpy(dest, src, sizeof(dest));

	printf("mine: %zu\n", ft_strlcpy(dest, src, size));
	printf("orig: %zu\n", strlcpy(dest, src, size));
	return (0);
}*/
