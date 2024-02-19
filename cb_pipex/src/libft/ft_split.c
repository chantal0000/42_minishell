/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:55:56 by chbuerge          #+#    #+#             */
/*   Updated: 2023/06/02 15:28:20 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
character ’c’ as a delimiter. The array must end
with a NULL pointer.*/

#include "libft.h"

/*count the number of words of a string by using a
specified delimiter character 'c'*/

int	count_words(const char *str, char c)
{
	size_t	result;
	int		setting;

	result = 0;
	setting = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str != c && setting == 0)
		{
			setting = 1;
			result++;
		}
		else if (*str == c)
			setting = 0;
		str++;
	}
	return (result);
}

/*creates a duplicate copy of each word extracted from the input string*/

char	*dup_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	size_t	j;
	char	**result;
	int		index;

	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (s == NULL || result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			result[j++] = dup_word(s, index, i);
			index = -1;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}

/*
#include <stdio.h>
#include <stdlib.h>


// Test the ft_split function
int main(void) {
    char const *s = "Hello,World,Split,Example";
    char **result = ft_split(s, ',');

    if (result == NULL) {
        printf("Error: Failed to split the string.\n");
        return 1;
    }

    // Print the split strings
    int i = 0;
    while (result[i] != NULL) {
        printf("%s\n", result[i]);
        i++;
    }

    // Free the memory allocated by ft_split
    i = 0;
    while (result[i] != NULL) {
        free(result[i]);
        i++;
    }
    free(result);

    return 0;
} */
