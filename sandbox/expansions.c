/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:03:09 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/05 20:04:35 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "variable_expansions.c"



char	*ft_var_name(char *s, t_exp *exp);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((strlen(s1) + strlen(s2)) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
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
			if (strchr((*temp)->cmd[i], '$'))
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
//	printf("exit\n");
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
//	while (s[i] && i != -1)
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			i++;
			if (s[i] == '?')
				printf("question mark found\n");
				//deal with ? here
//			else if (s[i] == '\'' || s[i] == '\"' || s[i] == ' ')
//				continue ;
		}
		else if (s[i] ==  '$' && (s[i + 1] == '\'' || s[i + 1] == '\"' || s[i + 1] == ' ' || s[i + 1] == '$'))
		{	
			continue ;
		}
		else
		{
			s = apply_expansion_magic(s, &i, exp);
		}
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
		if (s[*i] == '$' && (isalnum(s[*i + 1]) || s[*i + 1] == '_'))
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
	printf("name: %s\n", name);
	temp = exp;
	name_len = 0;
	var_exp = NULL;
	while(*name && (isalnum(*name)))// || *name == '_'))//goes to end of var name
	{
		name++;
	}
	while (temp)
	{
		if (strcmp(name, temp->exp_name) == 0)
		{
			printf("ok\n");
			if (temp->exp_value != NULL)
				var_exp = ft_strjoin(var_exp, temp->exp_value);
			else
			 	var_exp = ft_strjoin(var_exp, "");
			if (!var_exp)
				return (NULL);
		}
		temp = temp->next;
	}
	name_len = strlen(name);
	var_exp = ft_strjoin(var_exp, s + name_len);
	if (!var_exp)
		return (NULL);
	return (var_exp);
}

int main()
{
//	char	**arr;
	char	*s = "  va=12";
	char 	*t = "var=24";
	char	*test = "this$ba  ls";
	int		i = 0;
	t_exp	*exp;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
    // Populate the index
    cmd->index = 0;

    // Populate the command
    cmd->cmd[0] = strdup("echo");
    cmd->cmd[1] = strdup("$var");
    cmd->cmd[2] = NULL; // Null-terminate the command array

	exp = NULL;
	parse_for_expansions(&exp, &t);
	parse_for_expansions(&exp, &s);
	print_exp(exp);
	printf("cmd before expansion: %s\n", cmd->cmd[1]);

	cmd = *ft_find_var_expansions(&cmd, exp);
	printf("cmd after expansion: %s\n", cmd->cmd[1]);

    free(cmd->cmd[0]);
    free(cmd->cmd[1]);
	if (exp)
		free_exp(&exp);
	return (0);
}
