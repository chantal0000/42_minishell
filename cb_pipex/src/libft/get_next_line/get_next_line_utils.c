/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:15:47 by chbuerge          #+#    #+#             */
/*   Updated: 2024/01/15 16:23:27 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*combine the content of stash with the newly read content form fileat*/
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (0);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

/*
extracts a single line incl newline char
and returns new string
+ 2 -> for the \n and nulltermintor
extracts a line from the stash string
by iterating through it until it encounters
a newline character \n or reaches the end of the string.
It then dynamically
allocates memory for the extracted line and
copies the characters from stash
into new_str. Finally, it adds a newline character \n
at the end of new_str before
returning it.
*/

char	*ft_extract_line(char *stash)
{
	int		i;
	char	*new_str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (i + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		new_str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		new_str[i] = stash[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
i is the index where '\n' is found.
Subtracting i from ft_strlen(stat_str) gives the length of the remaining
portion of the string after '\n'
*/

char	*ft_remove_extracted_line_from_stash(char *stash)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(stash + i)));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_str[j++] = stash[i++];
	new_str[j] = '\0';
	free(stash);
	return (new_str);
}
