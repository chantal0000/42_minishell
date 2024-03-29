/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_and_groups.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/27 16:15:35 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*m_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst -> next;
	return (lst);
}

void	m_lstadd_back(t_cmd **lst, t_cmd *new)
{
	
	if (!lst || !new)
		return ;
	if (*lst)
	{
		new->prev = m_lstlast(*lst);
		new->next = NULL;
		m_lstlast(*lst)->next = new;
	}
	else
	{
		new->next = NULL;
		new->prev = NULL;
		*lst = new;
	}
}



//cmd is prev subtree and temp next subtree and if more pipes, 
//will create a new pipe node
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe)
{
	// t_cmd	*cmd;
	t_cmd	*temp;
	t_cmd	*temp2;

	// cmd = NULL;
	temp2 = NULL;
	if (!**str || !str)
		return ;
	 printf("now parsing for pipes\n");
	// printf("string in pipe: %s\n", *str);
	if (prev_pipe == 0)
	{
		temp = parse_exec_cmds(str);
		if (!temp)
			return ;
		m_lstadd_back(cmd, temp);
	}
	if (check_next_char(str, '|'))
	{
		// temp->next = temp2;
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL);
		temp2 = parse_exec_cmds(str);
		m_lstadd_back(cmd, temp2);
		// temp2->prev = temp;
		// temp2->next = NULL;
//		print_stack(*cmd);
		parse_for_pipe(str, cmd, 1);
	}
//	printf("\nEXIT PIPE PARSING FCN\n");
}

/*t_cmd	*parse_for_groups(char **s)
{
// 	t_cmd	*cmd;
// //	int		token;

// 	cmd = NULL;
// 	if (!**s || !s)
// 		return (0);
// 	printf("%s\n", *s);
// 	printf("now checking for groups\n");
// 	if (!check_next_char(s, '('))
// 	{
// 		printf("missing prev bracket");
// 		exit (1);
// 	}
// 	find_tokens(s, 0);
// 	printf("%s\n", *s);
// //	cmd = parse_for_pipe(s, cmd);
// 	if (!check_next_char(s, ')'))
// 	{
// 		printf("missing closing bracket\n");
// 		exit (1);//bash doesn't exit here...update it to match
// 	}
// 	printf("found closing bracket\n");
// 	printf("\nGROUP CLOSED\n");
// 	cmd = parse_for_redirections(cmd, s);
	return (NULL);
}*/


/*t_cmd	*parse_for_single(char **s)
{
	t_cmd	*cmd;

	if (!**s || !s)
		return (0);
	if (!check_next_char(s, '\''))
	{
		printf("missing prev bracket");
		exit (1);
	}
}
void	*parse_for_quotes(char *s)
{
	int		in_doubles;
	int		in_singles;
	char	replacement;
//	t_exec	cmd;
//	int		token;

	if (!*s || !s)
	{
		printf("string is empty");
		exit(1);
	}
	in_quotes = 0;
	in_singles = 0;
	replacement = \xFD;// or '\xA7';
//	printf("%s\n", *s);
//	printf("now checking for groups\n");
	while (*s)
	{
		if (*s == '"')
			in_doubles = !in_doubles;//opposite of current state
		if (*s == '\'');
			in_singles = !in_singles;
		if (in_doubles)
		if ((*s == '|' && !in_doubles) || (*s == '|' && *(s - 1) == '\\'))
			*s = replacement;
		*s++;
	}
}
void	restore_pipes(char *s)
{
	if (!*s || !s)
		return ;
	while (*s)
	{
		if (*s == '\xFD')
			*s = '|';
		*s++;
	}
}*/
