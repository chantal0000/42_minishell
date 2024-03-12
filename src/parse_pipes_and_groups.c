/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_and_groups.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 18:47:09 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cmd is left subtree and temp right subtree and if more pipes, 
//will create a new pipe node
t_cmd	*parse_for_pipe(char **str)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (!**str || !str)
		return (0);
	printf("now parsing for pipes\n");
	cmd = NULL;
	temp = build_cmd_tree(str);
//	printf("\nEXIT PIPE PARSE0\n");
//	exit(1);
	if (check_next_char(str, '|'))
	{
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL, NULL);
		cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (NULL);	
		cmd->type = PIPE;
		cmd->left = temp;
		cmd->right = parse_for_pipe(str);
		printf("\nEXIT PIPE PARSE1\n");
		return (cmd);
	}
	printf("\nEXIT PIPE PARSE2\n");
	return (temp);
}
