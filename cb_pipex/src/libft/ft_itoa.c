/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:06:26 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/26 20:18:52 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a string 
representing the integer received as an argument.
Negative numbers must be handled. 
This function converts an int into a string.*/

#include "libft.h"

int	ft_digit_len(int n)
{
	size_t	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			size;
	long		nb;	

	size = ft_digit_len(n);
	result = malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	nb = n;
	if (nb < 0)
		nb = nb * -1;
	result[size] = '\0';
	while (--size >= 0)
	{
		result[size] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int number = -12345;
    char *result = ft_itoa(number);
    printf("Number: %d\n", number);
    printf("Result: %s\n", result);
    free(result);

    number = 0;
    result = ft_itoa(number);
    printf("Number: %d\n", number);
    printf("Result: %s\n", result);
    free(result);

    number = 987654321;
    result = ft_itoa(number);
    printf("Number: %d\n", number);
    printf("Result: %s\n", result);
    free(result);

    return 0;
}*/
