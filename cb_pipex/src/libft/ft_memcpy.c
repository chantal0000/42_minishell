/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:46:27 by chbuerge          #+#    #+#             */
/*   Updated: 2023/06/05 11:26:40 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
The memcpy() function shall copy the first n bytes
pointed to by src to the buffer pointed to by dest.
Source and destination may not overlap.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*ptr_dest;
	const char	*ptr_src;

	i = 0;
	ptr_dest = (char *)dest;
	ptr_src = (const char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (ptr_dest);
}

/*
int main(void)
{

	char src[] = "Hello, world!";
    char dest[20];
	char dest1[20];


    ft_memcpy(dest, src, 6);


    printf("dest = %s\n", dest);
	printf("dest1 org = %s\n", memcpy(dest1, "Hello, world!", 6));
    return 0;
}*/
