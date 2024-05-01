/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:03:09 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/01 12:02:42 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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


char	*expansion_time(char *s, t_exp *exp)
{
	int	i;
	int	flag;

	i = 0;
	if (!s)
		return (NULL);
	flag = expansion_quotes(s);//returns 1 if in quotes
	while (s[i] && !flag && i != -1)
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			i++;
			if (s[i] == '?')
				printf("? found\n");
				//deal with ? here
//			else if (s[i] == '\'' || s[i] == '\"' || s[i] == ' ')
//				continue ;
		}
		else if (s[i] ==  '$' && (s[i + 1] == '\'' || s[i + 1] == '\"' || s[i + 1] == ' ' || s[i + 1] == '$'))
			continue ;
		else
			s = apply_expansion_magic(s, &i, exp);
		i++;
	}
	return (s);
}

int	expansion_quotes(char *s)
{
	int		in_quotes;
	char	*temp;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
	in_quotes = 0;
	temp = s;
	while (*temp)
	{
		if ((*temp == '\'' || *temp == '\"') && (*temp - 1) != '\\')
			in_quotes = !in_quotes;
		else if (*temp == '|' && (in_quotes))
		{
			*temp = '$';
			return (1);
		}
		temp++;
	}
	return (0);
}

char	*apply_expansion_magic(char *s, int *i, t_exp *exp)
{
	int flag;

	flag = expansion_quotes(s);
	if (!flag)
	{
		if (s[*i] == '$' && (ft_isalnum(s[*i + 1]) || s[*i + 1] == '_'))
		{
			s = ft_var_name(s, exp);
			if (s[*i] == '$' || s[*i] == '\"' || s[*i] == '\'')
				(*i)--;
			else if (s[*i] == 0)
				(*i) -= 2;
		}
//			else if (tok[*i] == '$' && state != 1)
//	{
//		tok = replace_var_wrongname(tok, i);
//		if (tok[*i] == '$' || tok[*i] == '"' || tok[*i] == '\'')
//			*i -= 1;
//		else if (tok[*i] == 0)
//			*i = -2;
	}
	return (s);
}

char	*ft_var_name(char *s, t_exp *exp)
{
	char	*name;
	char	*var_exp;
	int		name_len;
	t_exp	*temp;

	name = s + 1;//move past $
	temp = exp;
	name_len = 0;
	var_exp = NULL;
	while(*name && (ft_isalnum(*name) || *name == '_'))//goes to end of var name
		name++;
	while (temp)
	{
		if (ft_strcmp(name, temp->exp_name) == 0)
		{
			if (temp->exp_value != NULL)
				var_exp = ft_strjoin(var_exp, temp->exp_value);
			else
			 	var_exp = ft_strjoin(var_exp, "");
			if (!var_exp)
				return (NULL);
		}
		temp = temp->next;
	}
	name_len = ft_strlen(name);
	var_exp = ft_strjoin(var_exp, s + name_len);
	if (!var_exp)
		return (NULL);
	return (var_exp);
}
