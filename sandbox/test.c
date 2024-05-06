#include "../minishell.h"

void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, int *index);
char	*check_quotes(char *s);

int	is_token(char s)
{
	char	*tokens;

	tokens = "|<>()";
	if (strchr(tokens, s))
		return (1);
	return (0);
}

int	is_whitespace(char s)
{
	char	*whitespace;

	whitespace = " \n\t\r\v";
	if (strchr(whitespace, s))
		return (1);
	return (0);
}


void	free_cmdtree(t_cmd *tree)
{
	t_cmd	*temp;

	if (!tree)
		return ;
	while (tree)
	{
		temp = tree;
		temp = tree->next;
		if (tree->fd_in)
			close(tree->fd_in);
		if (tree->fd_out)
			close(tree->fd_out);
		if (tree->pid)
		{
			close(tree->pid);
		}
		if (tree->file_name)
			free(tree->file_name);
		free_memory(tree->cmd);
		free(tree);
		tree = temp;
	}
	free(tree);
}

void	free_memory(char **arr)
{
	int	i;

	i = 0;
	if (!*arr || !arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
}
t_cmd	*ft_init_struct(void)
{
	t_cmd	*cmd_tree;

	cmd_tree = (t_cmd *)calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
		return (NULL);
	return (cmd_tree);
}

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

int	check_for_alligators(char **s)
{
	int	token;

	token = **s;
	if (**s == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			token = '+';
			(*s)++;
		}
	}
	else if (**s == '<')
	{
		(*s)++;
		if (**s == '<')
		{
			token = '-';
			(*s)++;
		}
	}
	return (token);
}

int	find_tokens(char **s, char **beg_of_file)
{
	int		token;
	char	*line;

	line = *s;
	while (*line != '\0' && is_whitespace(*line))
		line++;
	if (beg_of_file)
		*beg_of_file = line;
	token = *line;
	if (*line == '\0')
		return (token);
	else if (*line == '|' || *line == '(' || *line == ')')
		line++;
	else if (*line == '>' || *line == '<')
		token = check_for_alligators(&line);
	else
	{
		token = 'a';
		while (*line != '\0' && !is_whitespace(*line) && !is_token(*line))
			line++;
	}
	while (*line != '\0' && is_whitespace(*line))
		line++;
	*s = line;
	return (token);
}

void	parse_for_cmds(t_cmd **cmd, char *s)
{
	int		index;

	if (!s)
		return ;
	index = 0;
	parse_for_pipe(&s, cmd, 0, &index);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	if (*s != '\0')
	{
		printf("check syntax\n");//check what bash returns
		return ;
	}
	restore_pipes_and_spaces(*cmd);
}

int	check_next_char(char **s, char token)
{
	char	*temp;

	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	*s = temp;
	if (**s != '\0' && **s == token)
		return (1);
	return (0);
}

void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, int *index)
{
	t_cmd	*temp;
	t_cmd	*temp2;
	char	*copy;

	temp2 = NULL;
	if (!**str || !str)
		return ;
	if (prev_pipe == 0)
	{
		temp = parse_exec_cmds(str);
		if (!temp)
			return ;
		temp->index = *index;
		m_lstadd_back(cmd, temp);
	}
	(*index)++;
	if (check_next_char(str, '|'))
	{
		str_copy = strdup(*str);
		find_tokens(&str_copy, NULL);
		temp2 = parse_exec_cmds(str);
		temp2->index = *index;
		m_lstadd_back(cmd, temp2);
		parse_for_pipe(&str_copy, cmd, 1, index);
		free(str_copy);
	}
}

void	restore_pipes_and_spaces(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd;
	while (temp)
	{
		while (temp->cmd[i])
		{
			ft_restore(temp->cmd[i]);
			i++;
		}
		temp = temp->next;
	}
}

void	ft_restore(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (*s == '\xFD')
			*s = '|';
//		if (*s == '\xFE')
  		if (*s == '\x7F')
			*s = ' ';
		s++;
	}
}

char	*parse_line(char *arr)
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

t_cmd	*init_exec_cmds(char **s, char *non_token)
{
	int		i;
	int		token;
	t_cmd	*cmd_tree;

	i = 0;
	token = 0;
	cmd_tree = ft_init_struct();
//	cmd_tree = parse_for_redirections(cmd_tree, s);
	if (!cmd_tree)
		return (NULL);
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		if (token == 0)
			break ;
		cmd_tree->token = token;
		cmd_tree->cmd[i] = strdup(non_token);
		if (!cmd_tree)
		{
			free_memory(s);
			free (non_token);
			printf("error copying cmd into array");
			exit (1);
		}
		parse_line(cmd_tree->cmd[i]);
//		cmd_tree->cmd[i] = check_quotes(cmd_tree->cmd[i]);
		i++;
//		cmd_tree = parse_for_redirections(cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	return (cmd_tree);
}

t_cmd	*parse_exec_cmds(char **s)
{
	t_cmd	*cmd_tree;
	char	*non_token;

	non_token = NULL;
	cmd_tree = (t_cmd *)calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
	{
		printf("cmd_tree initiation in exec failed\n");
		exit (1);
	}
	cmd_tree = init_exec_cmds(s, non_token);
	if (!cmd_tree)
		free_cmdtree(cmd_tree);
	return (cmd_tree);
}

int	main()
{
	static char	*line = "ls | wc";
	t_cmd	*list;

	list = NULL;
	while (1)
	{
		parse_for_cmds(&list, line);//need to add envp
		free_cmdtree(list);
		list = NULL; // here needs to be freed
	}
	return (0);
}