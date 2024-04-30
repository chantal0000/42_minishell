/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:38:21 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/30 17:10:26 by kbolon           ###   ########.fr       */
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
	len = strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		temp = (char *)malloc(sizeof(char) * (len - 2));
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
	s = temp;
	free(temp);
	return (s);
}

char	**shell_split(char *s, char delimiter)
{
	char	**arr;
	char	*end;
	char	*var_end;

	var_end = NULL;
	arr = (char **)calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	end = s;
	while (*end != '\0' && *end != delimiter)
		end++;
	if (*end == delimiter)
	{
		arr[0] = strndup(s, end - s);
		if (!arr[0])
		{
			printf("problems mem alloc in ex split");
			exit (1);
		}
		end = check_quotes(end);
		//parse for quotes???
		arr[1] = strdup(end + 1);
		if (!arr[1])
		{
			free(arr[0]);
			printf("problems mem alloc in ex split");
			exit (1);
		}
		var_end = arr[1];
		while (*var_end != ' ' && *var_end != '\0' && *var_end != '|')
			var_end++;
		*var_end = '\0';
	}
	arr[2] = NULL;
	arr[1] = check_quotes(arr[1]);
	return (arr);
}

/*void	ft_find_var_declarations(char **s, t_exp **exp)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	temp = *s;
	while (temp[i] != '\0' && is_whitespace(temp[i]))
		i++;
	while (temp[i] != '\0')
	{
		if (temp[i] == '=')
		{
			j = i - 1;
			while (j >= 0 && (temp[j] == ' ' || temp[j] == '|'))
				j--;
			if (j >= 0)
			{
				arr = shell_split(*s, '=');
				if (!arr)
				{
					printf("problems splitting shell in exp finder\n");
					exit (0);
				}
				*exp = insert_exp(*exp, arr[0], arr[1]);
				free_memory(arr);
//				while (temp[i] != '\0' && is_whitespace(temp[i]))
//					i++;
			}
		}
		i++;
	}
	while (temp[i] != '\0' && is_whitespace(temp[i]))
		i++;
	if (temp[i] != '\0' && !is_whitespace(temp[i]))
		printf("open heredoc?\n");//check what bash returns
	temp += i;
	*s = temp;
//	return (exp);
}*/

void ft_find_var_declarations(char **s, t_exp **exp)
{
	char *temp;
	char *start;
	char *value_start;

	temp = *s;
	while (*temp && is_whitespace(*temp))//while not at end and is a whitespace
		temp++;
	while (*temp)//while not at end
	{
		start = temp; 
//		while (*temp && *temp != '=' && !is_whitespace(*temp))
//			temp++;
		if (*temp == '=')
		{
			temp++;
			value_start = temp;
			while (*temp && !is_whitespace(*temp))
				temp++;
			char *name = strndup(start, value_start - start - 1);
			char *value = strndup(value_start, temp - value_start);
			*exp = insert_exp(*exp, name, value);
			free(name);
			free(value);
			while (*temp && is_whitespace(*temp))
				temp++;
		} 
		else
			break;
	}
	*s = temp;
}

t_cmd	**ft_find_var_expansions(t_cmd **cmd, t_exp *exp)
{
	int		i;
	int		j;
	t_cmd	**temp;

	temp = cmd;
	while(*temp)
	{
		i = 0;
		while ((*temp)->cmd[i])
		{
			j = 0;
			if (ft_strchr((*temp)->cmd[i], '$'))
			{
				printf("$ found: %s\n", (*temp)->cmd[i]);
				printf("exp: %s\n", exp->exp_name);
				(*temp)->cmd[i] = expansion_time((*temp)->cmd[i], exp);
			}
			while ((*temp)->cmd[i][j])
			{
				if ((*temp)->cmd[i][j] != ' ')
					break ;
				j++;
			}
			i++;
		}
		*temp = (*temp)->next;
		cmd = temp;
	}
	return (cmd);
}
