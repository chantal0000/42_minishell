/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:39:16 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/15 12:56:47 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	i = 0;
	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	if (size == 0)
		return (s_len);
	while (src[i] && d_len + i < size -1)
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	if (d_len > size)
		return (s_len + size);
	return (s_len + d_len);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char dest[20];
    const char *src = "Hello, world!";
    size_t size = sizeof(dest);
    size_t len;

    len = ft_strlcpy(dest, src, size);
    printf("Copied string: %s\n", dest);
    printf("Returned length: %zu\n", len);

    return 0;
}*/
