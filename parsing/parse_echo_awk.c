/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/18 16:51:06 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*echo_cmds(char **s)
{
	int		i;
	t_cmd	*cmd_tree;

	i = 0;
	cmd_tree = ft_init_struct();
	cmd_tree = parse_for_redirections(cmd_tree, s);
	if (ft_strncmp(*s, "echo", 4) == 0)
		cmd_tree = ft_echo(cmd_tree, s);
	return (cmd_tree);
}

	
t_cmd	*ft_echo(t_cmd *cmd_tree, char **s)
{
	int		i;
	int		len;
	t_cmd	*temp;
	char	*arg_start;
	char	*file_name;

	i = 0;
	temp = cmd_tree;
	len = 0;
	file_name = NULL;
	find_tokens(s, &file_name);
	if (ft_strncmp(file_name, "echo", 4) == 0)
	{
		temp->cmd[i] = parse_line(ft_strdup(file_name));
		arg_start = *s;
		printf("s in loop: %s\n", *s);
		while (arg_start[len] != '|' && arg_start[len] != '\0')
			len++; 
		i++;
		temp->cmd[i] = ft_strndup(arg_start, len);
		arg_start += len;
		temp->cmd[3] = NULL;
		cmd_tree = temp;
		*s = arg_start + 1;
	}
	printf("in loop cmd[0]: %s\n", temp->cmd[0]);
	printf("in loop cmd[1]: %s\n", temp->cmd[1]);
	return (cmd_tree);
}

char	*parse_line_echo(char *arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] != '\0' && (!is_whitespace(arr[i]) && !is_token(arr[i])))
		i++;
	arr[i] = '\0';
	return (arr);
}

int	is_echo_token(char s)
{
	char	*tokens;

	tokens = "\'\"";
	if (ft_strchr(tokens, s))
		return (1);
	return (0);
}

/*int	parse_quotes_for_echo(char *s)
{
	int		in_single;
	int		in_double;
	int		i;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
	i = 0;
	in_single = 0;
	in_double = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && (s[i - 1]) != '\\' && !in_double)
		{
			i++;
			in_single = !in_single;
			while (s[i] != '\'' && (s[i - 1]) != '\\' && s[i] != '\0' && s[i] != '|')
				i++;
			return (i);
		}
		else if (s[i] == '\"' && (s[i - 1]) != '\\' && !in_single)
		{
			i++;
			in_double = !in_double;
			while (s[i] != '\"' && (s[i - 1]) != '\\' && s[i] != '\0' && s[i] != '|')
				i++;
			return (i);
		}
		else
		{
			while (s[i] != '|' && s[i] != '\0')
				i++;
//			return (i);
		}
	}
	return (i);
}*/
