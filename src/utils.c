/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:24 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/15 16:30:22 by kbolon           ###   ########.fr       */
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
/*char	*shell_split(t_exp exp, char *s, char c)
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
	while (s[i] != '\0' && s[i] != c)
		i++;
	arr[0] = ft_calloc(i + 1, sizeof(char));
	if (!arr[0])
	{
		printf("problems mem alloc in ex split");
		exit (1);
	}
	ft_memcpy(arr[0], s, i);
	arr[0][i + 1] = '\0';
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
}*/

void	parse_string(char *s)
{
	char	*temp;

	temp = s;
	if (*temp != '\0')
	{
		while (*temp != '\0')
		{
			if (*temp != '\0' && is_whitespace(*temp))
			{
				printf("open heredoc?\n");//check what bash returns
				return ;
			}
			temp++;
		}
	}
	s = temp;
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		if (size > 0)
			dst[i] = '\0';
	}
	return (src_len);
}

size_t	ft_strncat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	d = dst_len;
	while (src[d = dst_len] && d < size - 1)
	{
		dst[d] = src[d - dst_len];
		d++;
	}
	dst[d] = '\0';
	return (dst_len + src_len);
}
