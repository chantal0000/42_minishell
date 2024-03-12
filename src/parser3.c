/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/12 15:11:27 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*redir_cmd(t_cmd *cmd, char *beg_file, char *end_file, int instructions, int fd)
{
	t_redir	*redirection;

	redirection = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redirection)
		return (NULL);
	redirection->type = REDIR;
	redirection->cmd = cmd;
	redirection->beg_file = beg_file;
	redirection->end_file = end_file;
	redirection->instructions = instructions;
	redirection->fd = fd;
	return ((t_cmd *)redirection);
}

t_cmd	*parse_for_groups(char **s)
{
	t_cmd	*cmd;

	printf("now checking for groups\n");
	if (!check_next_char(s, '('))
	{
		printf("missing left bracket");
		exit (1);
	}
	find_tokens(s, NULL , NULL);
	cmd = parse_for_pipe(s);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket\n");
		exit (1);//bash doesn't exit here...update it to match
	}
	printf("found closing bracket\n");
	printf("\nGROUP CLOSED\n");
//	cmd = parse_for_redirections(cmd, s);
	return (cmd);
}


t_cmd	*parse_exec(char **s, t_exec *cmd_tree, char *cmd, char *opt)
{
	int		i;
	int		token;

	i = 0;
	token = 0;
	printf("\nin parse_exec\n");
	while (!check_next_char(s, '|') && !check_next_char(s, ')'))// && !check_next_char(&s, ')'))
	{
		if (!(token = find_tokens(s, &cmd, &opt)))//do I need?  I am looking for only 'a'
			break ;
		else if (token != 'a')
		{
			printf("please enter valid commands\n");
			return (NULL);
		}
		printf("cmd: %c\n", *cmd);
		printf("opt: %c\n", *opt);
		cmd_tree->cmd[i] = cmd; //pointer to token
		cmd_tree->options[i] = opt; //pointer to space after token
		i++;
		if (i > MAXARGS)//do I need?
		{
			printf("too many args");
			exit (1);
		}
//		cmd_tree = (t_exec *)parse_for_redirections((t_cmd *)cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	cmd_tree->options[i] = NULL;
	return ((t_cmd *)cmd_tree);
}

t_cmd	*build_cmd_tree(char **s)
{
	t_cmd	*cmd_tree;
	char	*cmd;
	char	*opt;

	cmd = NULL;
	opt = NULL;
	printf("now building cmd tree\n");
	if (check_next_char(s, '('))
	{
		printf("\nGROUP FOUND\n\n");
		cmd_tree = parse_for_groups(s);
		return (cmd_tree);
	}	
	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
		return (NULL);
	cmd_tree->type = EXEC;
//	cmd_tree = parse_for_redirections(cmd_tree, s);
	cmd_tree = parse_exec(s, (t_exec *)cmd_tree, cmd, opt);
	if(!cmd_tree)
		free (cmd_tree);
	return (cmd_tree);
}

/*t_cmd	*parse_for_redirections(t_cmd *cmd, char **s)
{
//	int		token;
	char	*beg_of_file;
	char	*end_of_file;

	printf("now parsing for redirections\n");
	while (check_next_char(s, '<') || check_next_char(s, '>'))
	{
		printf("in while loop\n");
//		token = find_tokens(s, 0, 0);
//		printf("token: %d\n", token);
		find_tokens(s, 0, 0);
		if (find_tokens(s, &beg_of_file, &end_of_file) != 'a')
		{
			printf("missing file");//need to change to follow bash
			return ((void *)0);
		}
		if (**s == '>')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_WRONLY | O_CREAT | O_TRUNC, 1);//fd=1
		else if (**s == '<')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_RDONLY, 0);//fd=0
		else if (**s == '+')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file,  O_WRONLY | O_CREAT, 1);//fd=1
		else if (**s == '-')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_RDONLY, 0);//fd=0
		else
			return ((void *)0);
	}
	return (cmd);
}*/


