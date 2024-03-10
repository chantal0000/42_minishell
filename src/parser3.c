/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:46 by kbolon            #+#    #+#             */
/*   Updated: 2024/03/10 10:48:49 by kbolon           ###   ########.fr       */
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
	find_tokens(s, NULL , NULL);//move to token
	printf("now checking for pipes again\n");
	cmd = ft_parse_for_pipe(s);
	if (!check_next_char(s, ')'))
	{
		printf("missing closing bracket");
		exit (1);//bash doesn't exit here...update it to match
	}
	find_tokens(s, 0, 0);//move to next token
	cmd = parse_for_redirections(cmd, s);
	cmd = build_cmd_tree(s);
	return (cmd);
}


t_cmd	*parse_exec(char **s, t_exec *cmd_tree, char *cmd, char *opt)
{
	int		i;
	int		token;

	i = 0;
	token = 0;
	while (!check_next_char(s, '|'))// && !check_next_char(&s, ')'))
	{
		if (!find_tokens(s, &cmd, &opt))
			break ;
		else if (token != 'a')
		{
			printf("please enter valid commands\n");
			return ((void *)0);
		}
		cmd_tree->cmd[i] = cmd;
		cmd_tree->options[i] = opt;
		i++;
		cmd_tree = (t_exec *)parse_for_redirections((t_cmd *)cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	cmd_tree->options[i] = NULL;
	return ((t_cmd *)cmd_tree);
}

t_cmd	*build_cmd_tree(char **s)
{
	t_exec	*temp;
	t_cmd	*cmd_tree;
	char	*cmd;
	char	*opt;

	cmd = NULL;
	opt = NULL;
	printf("now building cmd tree\n");
	if (check_next_char(s, '('))
	{
		printf("now checking for left bracket\n");
		cmd_tree = parse_for_groups(s);
		return (cmd_tree);
	}
	temp = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!temp)
		return ((void *)0);
	temp->type = EXEC;
	cmd_tree = (t_cmd *)temp;
	cmd_tree = parse_for_redirections((t_cmd *)cmd_tree, s);
	if(!parse_exec(s, (t_exec *)cmd_tree, cmd, opt))
		free_cmd_tree((t_exec *)cmd_tree);
	return (cmd_tree);
}

t_cmd	*parse_for_redirections(t_cmd *cmd, char **s)
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
/*		if (**s == '>')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_WRONLY | O_CREAT | O_TRUNC, 1);//fd=1
		else if (**s == '<')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_RDONLY, 0);//fd=0
		else if (**s == '+')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file,  O_WRONLY | O_CREAT, 1);//fd=1
		else if (**s == '-')
			cmd = redir_cmd(cmd, beg_of_file, end_of_file, O_RDONLY, 0);//fd=0
		else
			return ((void *)0);*/
	}
	return (cmd);
}


