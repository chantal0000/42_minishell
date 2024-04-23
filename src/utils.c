/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:24 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/23 15:02:57 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc (sizeof(char) * (n + 1));
	if (p == 0)
		return (0);
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**export_split(char	*s)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)ft_calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	while (s[i] != '\0' && s[i] != '=')
		i++;
	arr[0] = ft_calloc(i + 2, sizeof(char));//+2 for (= '/0')
	if (!arr[0])
	{
		printf("problems mem alloc in ex split");
		exit (1);
	}
	ft_memcpy(arr[0], s, i + 1);
	arr[0][i + 2] = '\0';
	arr[1] = ft_calloc(ft_strlen(s) - i + 1, sizeof(char));
	if (!arr[1])
	{
		free_memory(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	ft_memcpy(arr[1], &s[i + 1], ft_strlen(s) - i);
	arr[1][ft_strlen(s) - 1] = '\0';
	arr[2] = NULL;
	check_quotes(arr[1]);
	return (arr);
}
