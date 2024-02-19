/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:53:43 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/17 16:46:01 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*
#include <stdio.h>

int main ()
{
	const char *original = "yaaaay ayayaya";
	char *copy = ft_strdup(original);

	printf("original %s\n", original);
	printf("copy %s\n", copy);

	free(copy);
	
	return 0;
}*/
