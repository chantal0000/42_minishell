/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:58:27 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/17 15:49:41 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	result = malloc(nmemb * size);
	if (result == NULL)
		return (0);
	while (i < nmemb * size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
/*
#include <stdio.h>
int  main(void)
{
	int *n;
	int *n1;
	size_t numElements = 5;
	int i;
	
	i = 0;
	n = (int *)ft_calloc(numElements, sizeof(int));
	n1 = (int *)malloc(numElements * sizeof(int));
	
	while (i < numElements)
	{
		n[i] = i + 1;

		i++;
	}

	printf("array calloc: %d %d %d %d %d\n", n[0], n[1], n[2], n[3], n[4]);
	printf("array malloc: %d %d %d %d %d\n", n1[0], n1[1], n1[2], n1[3], n1[4]);
	free(n);

	return (0);
}*/
