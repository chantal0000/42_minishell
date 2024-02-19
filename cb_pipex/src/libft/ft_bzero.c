/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:57:00 by chbuerge          #+#    #+#             */
/*   Updated: 2023/06/05 10:17:28 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
The  bzero()  function  erases  the  data  in the n bytes of the memory
starting at the location pointed to by s, by writing zeros (bytes  con‐
taining '\0') to that area.
*/
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*ptr = 0;
		ptr++;
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[50] = "hello world";
	printf("Before bzero: %s\n", str);
	ft_bzero(str, 5);
	printf("After bzero: %s\n", str);
	return (0);
}*/
