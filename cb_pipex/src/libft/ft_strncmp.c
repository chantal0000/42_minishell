/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:48:19 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/12 12:04:53 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int main(void)
{
	printf("mine p: %d\n", ft_strncmp("hell", "hel"));
	printf("orig p: %d\n", strncmp("hell", "hel"));

	printf("mine 0: %d\n", ft_strncmp("hell", "hell"));
    printf("orig 0: %d\n", strncmp("hell", "hell"));

	printf("mine n: %d\n", ft_strncmp("he", "hel"));
    printf("orig n: %d\n", strncmp("he", "hel"));

	
	return (0);
}*/
