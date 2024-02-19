/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:34:58 by chbuerge          #+#    #+#             */
/*   Updated: 2023/05/30 10:58:32 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
#include <stdio.h> // Include necessary header files

// Test function to be passed as the function argument in ft_strmapi
char f(unsigned int index, char c)
{
    // Add 1 to the ASCII value of the character at the given index
    return c + 1;
}

int main()
{
    // Input string to test ft_strmapi
    char input[] = "hello";

    // Call ft_strmapi with the input string and the test function
    char *result = ft_strmapi(input, f);

    if (result == NULL)
    {
        printf("Allocation failed. Unable to create the new string.\n");
        return 1;
    }

    printf("Original string: %s\n", input);
    printf("Transformed string: %s\n", result);

    // Remember to free the dynamically allocated memory
    free(result);

    return 0;
}*/
