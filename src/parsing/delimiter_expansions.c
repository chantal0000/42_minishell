/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:21 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/27 15:27:42 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	size_t		i;
	size_t		len;
	char		*temp;

	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			temp = (char *)malloc(sizeof(char) * len - 2);
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

char	**shell_split(char *s, char c)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	while (s[i] != '\0' && s[i] != c)
		i++;
	arr[0] = strndup(s, i);
	if (!arr[0])
	{
		printf("problems mem alloc in ex split");
		exit (1);
	}
	arr[1] = strndup(s + i + 1, strlen(s) - i - 1);
	if (!arr[1])
	{
//		free_memory(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	arr[2] = NULL;
	check_quotes(arr[1]);
	return (arr);
}

t_exp	*ft_find_var_declarations(t_cmd **cmd)
{
	int		i;
	char	**arr;
	t_exp	*exp;
	t_cmd	**temp;

	i = 0;
	exp = NULL;
	temp = cmd;
	while (temp[0]->cmd[0][i] != '\0')
	{
		if (temp[0]->cmd[0][i] == '=')
		{
			arr = shell_split(temp[0]->cmd[0], '=');
				if (!arr)
					return (NULL);
			exp = insert_exp(exp, arr[0], arr[1]);
			temp[0]->token = 'v';
			printf("what to do\n");
			temp[0]->cmd[0] = "";
		}
		i++;
	}
	cmd = temp;
	return (exp);
}

void	ft_find_var_expansions(t_cmd **cmd, t_exp *exp)
{
	int		i;
	t_cmd	**temp;

	temp = cmd;
	while(*temp)
	{
		i = 0;
		while ((*temp)->cmd[i])
		{
			if (ft_strchr((*temp)->cmd[i], '$'))
			{
				printf("$ found: %s\n", (*temp)->cmd[i]);
				printf("cmd[%d]: %s\n", i, (*temp)->cmd[i]);
				printf("exp: %s\n", exp->exp_name);
			}
			i++;
		}
		*temp = (*temp)->next;
		cmd = temp;
	}
}
