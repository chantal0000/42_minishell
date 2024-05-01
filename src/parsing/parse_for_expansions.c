/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:59:39 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/01 21:00:15 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//function checks if there are quotes after '='
/*char	*check_quotes_var(char **s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	i = 0;
	len = strlen(*s);
	temp = *s;
	if ((temp[0] == '\'' && temp[len - 1] == '\'') || (temp[0] == '\"' && temp[len - 1] == '\"'))
	{
		temp = (char *)malloc(sizeof(char) * (len - 2));
		if (!temp)
		{
			printf("problems mem alloc checkquotes");
			exit (1);
		}
		while (i < len - 2)
		{
			temp[i] = (*s)[i + 1];
			i++;
		}
		temp[i] = '\0';
	}
	free(*s);
	return (temp);
}*/
//function checks if token or quotes before variable declaration
//continues if quotes are found
int	check_for_var(char **line, t_exp **exp)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if (ft_strchr(*line, '='))
	{
		found = 1;
		while (*line && is_whitespace(**line))
			(*line)++;
		if (**line == '\'' || **line == '\"')
		{
			printf("found quotes in check_for_var fcn\n");
			return (found);
		}
		while ((*line)[i] != '\0')
		{
			if ((*line)[i] == '=')
				break ;
			else if (is_token((*line)[i]))
			{
				printf("Token found before '='\n");
				return (found);
			}
			i++;
		}
		ft_find_var_declarations(line, exp);
		parse_string(*line);
	}
	return (found);
}

//this creates arr in t_exp struct and calls fcn to populate
char	**shell_split(char **s, char delimiter)
{
	char	**arr;
	char	*end;

	arr = (char **)calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	end = *s;
	while (*end != '\0' && *end != delimiter)
		end++;
	if (*end == delimiter)
	{
		arr = fill_array(arr, s, end);
		if (!arr)
		{
			free_memory(arr);
			return (NULL);
		}
	}
	return (arr);
}
//this function populates arr in exp struc
char	**fill_array(char **arr, char **s, char *end)
{
	char	*var_end;

	arr[0] = ft_strndup(*s, end - *s);
	if (!arr[0])
	{
		free(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	var_end = end;
	while (*var_end != ' ' && *var_end != '\0' && *var_end != '|')
		var_end++;
	arr[1] =ft_strndup(end + 1, var_end - (end + 1));
	if (!arr[1])
	{
		free_memory(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	*s = var_end;
	arr[2] = NULL;
	arr[1] = check_quotes(arr[1]);
	return (arr);
}

//this funciton searches for '=' and if none found
//continues to command functions and regular parsing
void	ft_find_var_declarations(char **s, t_exp **exp)
{
	int		i;
	int		j;
	char	**arr;
	char	*temp;

	i = 0;
	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	while (temp[i] != '\0')
	{
		if (temp[i] == '=')
		{
			j = i - 1;
			while (j >= 0 && (temp[j] == ' '))
				j--;
			if (j >= 0)
			{
				arr = shell_split(&temp, '=');
				if (!arr)
				{
					printf("problems splitting shell in exp finder\n");
					exit (0);
				}
				*exp = insert_exp(*exp, arr[0], arr[1]);
//				free_memory(arr);
			}
		}
		i++;
	}
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	i = strlen (temp);
	if (i != 0)
		printf("open heredoc?\n");//check what bash returns
	*s = temp;
}
