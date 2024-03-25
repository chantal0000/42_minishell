/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_and_groups.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:12:07 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/25 14:51:37 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cmd is prev subtree and temp next subtree and if more pipes, 
//will create a new pipe node
/*t_cmd	*parse_for_pipe(char **str)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	t_cmd	*new_cmd;
	int		token;

	if (!**str || !str)
		return (0);
	token = 0;
	if (!cmd)
		return (NULL);
	token = check_next_char(str, '|');
	if (token == 1)
	{
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL);
		temp = parse_for_pipe(str);
		new_cmd = init_pipe(cmd, temp);
		if (!new_cmd)
			return (NULL);
		return (new_cmd);
	}
	else
	{
		cmd = parse_exec_cmds(str);
		if (!cmd)
			return (NULL);
		temp = parse_for_pipes(str);
		if (!temp)
			return (NULL);
		new_cmd = init_pipe(cmd, temp);
		if (!new_cmd)
			return (NULL);
		return (new_cmd);
	}
	
	return (cmd);
}*/

t_cmd	*parse_for_pipe(char **str, int *i, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	t_cmd	*new_cmd;
	int		token;

	if (!**str || !str)
		return (0);
	printf("in parse for pipe\n");
	token = 0;
	cmd = NULL;
	temp = NULL;
	//initiate cmd here and pass it to parse_exec_cmds empty???
	cmd = parse_exec_cmds(str, i, envp);
	if (!cmd)
		return (NULL);
	token = check_next_char(str, '|');
	if (token == 1)//if pipe found
	{
		printf("\nPIPE FOUND\n\n");
		find_tokens(str, NULL);
		temp = parse_for_pipe(str, i, envp);
		if (!temp)
			return (NULL);
		new_cmd = build_cmd_tree(cmd, temp, i, envp);
		if (!new_cmd)
			return (NULL);
		printf("node index %d\n", new_cmd->index);
		return (new_cmd);
	}
/*
	{
		cmd = parse_exec_cmds(str, i, envp);
		if (!cmd)
			return (NULL);
		// Now, check if there is a pipe after the current command
		token = check_next_char(str, '|');
		if (token == 1)
		{
			printf("PIPE FOUND\n");
			find_tokens(str, NULL);
			temp = parse_for_pipe(str, i, envp);
			if (!temp)
				return (NULL);
//			new_cmd = init_pipe(cmd, temp, i);
			new_cmd = build_cmd_tree(cmd, temp, i, envp);
//			new_cmd->index = *i;
			if (!new_cmd)
				return (NULL);
			printf("node index %d\n", new_cmd->index);
			printf("prev %d\n", new_cmd->prev->type);
			printf("next %d\n", new_cmd->next->type);

			return (new_cmd);
		}*/
	else
		return (cmd);
}

t_cmd	*parse_for_groups(char **s, int *i, char **envp)
{
	t_cmd	*cmd;

	if (!**s || !s)
		return (0);
	if (!check_next_char(s, '('))
	{
		printf("missing prev bracket");
		exit (1);
	}
	find_tokens(s, 0);
	cmd = parse_for_pipe(s, i, envp);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("\nGROUP CLOSED\n");
	find_tokens(s, 0);
	cmd = parse_for_redirections(cmd, s, i, envp);
	return (cmd);
}

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
