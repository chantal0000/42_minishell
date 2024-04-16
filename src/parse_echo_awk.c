/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:21:12 by kbolon            #+#    #+#             */
/*   Updated: 2024/04/16 17:03:20 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_echo(t_cmd *cmd_tree, char **s)
{
	int		i;
	int		token;
	char	*non_token;

	i = 0;
	cmd_tree = ft_init_struct();
	non_token = NULL;
	printf("string in ft_echo: %s\n", *s);
	if (ft_strncmp(*s, "echo", 4) == 0)
	{
		while (**s && !is_whitespace(**s) && !is_echo_token(**s))
		{
			token = find_tokens(s, &non_token);
			if (token == 0)
				break ;
			cmd_tree->token = token;
			cmd_tree->cmd[i] = ft_strdup(non_token);
			if (!cmd_tree)
			{
				free_memory(s);
				free (non_token);
				printf("error copying cmd into array");
				exit (1);
			}
			parse_line(cmd_tree->cmd[i]);
			printf("cmd->[%d]: %s", i, cmd_tree->cmd[i]);
			i++;
			s++;
		}
		cmd_tree->cmd[i] = NULL;
	}
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