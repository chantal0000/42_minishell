/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_variable_exp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:25:16 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/05 13:26:23 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exp	*insert_exp(t_exp *head, char *name, char *value)
{
	t_exp	*new_node;
	t_exp	*temp;

	new_node = (t_exp *)ft_calloc(1, sizeof(t_exp));
	if (!new_node)
		return (NULL);
	new_node->exp_name = ft_strdup(name);
	new_node->exp_value = ft_strdup(value);
	new_node->next = NULL;
	if (!head)
		return (new_node);
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (head);
}

//function returns 1 if a parsable '=' is found
//parsable means not in quotes or token found before '='
int	search_string_for_equal(char *s)
{
	char	*temp;
	int		i;

	i = 0;
	temp = s;
	while (is_whitespace(*temp))
		temp++;
	if (strchr(temp, '='))
	{
		while (temp[i] != '\0' && temp[i] != '=' && temp[i] != '\'' && \
			temp[i] != '\"' && !is_token(temp[i]))
			i++;
		if (temp[i] == '=')
			return (1);
	}
	return (0);
}

char	*find_name(char **s)
{
	int		i;
	char	*name;
	char	*temp;

	i = 0;
	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	while (temp[i] != '\0' && temp[i] != '=')
		i++;
	name = ft_strndup(temp, i + 1);
	if (!name)
		return (NULL);
	*s = &temp[i];
	return (name);
}

char	*find_value(char **s)
{
	int		i;
	char	*temp;
	char	*value;

	temp = *s;
	i = 0;
	if (*temp == '=')
		temp++;
	while (temp[i] != '\0' && !is_token(temp[i]) && !is_whitespace(temp[i]))
		i++;
	value = ft_strndup(temp, i + 1);
	if (!value)
		return (NULL);
	value = check_quotes(value);
	if (!value)
		return (NULL);
	while (temp[i] != '\0' && is_whitespace(temp[i]))
		i++;
	*s = &temp[i];
	return (value);
}

void	parse_for_expansions(t_exp **exp, char **s)
{
	char	*name;
	char	*value;

	if (search_string_for_equal(*s) == 1)
	{
		name = find_name(s);
		value = find_value(s);
		*exp = insert_exp(*exp, name, value);
		free (name);
		free (value);
	}
}
