/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:24 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/12 17:58:41 by kbolon           ###   ########.fr       */
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

/*int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0') && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}*/

int	find_delimiter(char *s1, char *delim)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("in find delimiter \n");
	while (s1[i] != '\0' && delim[j] != '\0' && s1[i] == delim[j])
	{
		i++;
		j++;
	}
	if (delim[j] == '\0')
		return (1);
	printf("out find delimiter \n");
	return (0);
}

char	*check_quotes(char *s)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			temp = (char *)malloc(sizeof(char) * len -2);
			if (!temp)
			{
				printf("problems mem alloc checkquotes");
				exit (1);
			}
			while (i < len - 2)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
		}
	}
	return (temp);
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
