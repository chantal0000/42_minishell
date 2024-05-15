#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_cmd t_cmd;
typedef struct s_env t_env;
typedef struct s_exp t_exp;

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
	char	*cmd_env;
	t_env	*next; // pointer to the next node in the linked list

}	t_env;

typedef struct s_exp
{
	char	*exp_name;
	char	*exp_value;
	t_exp	*next;
}	t_exp;


typedef struct s_cmd
{
	t_env	*m_env;
	t_exp	*exp;
	int		token;
	char	*cmd[MAXARGS + 1];
	char	*file_name;
	int		instructions;
	int		fd_in;
	int		fd_out;
	int		pid;
	t_cmd	*prev;
	t_cmd	*next;
	char	*heredoc_delimiter;
	char	*heredoc_content[MAX_CONTENT_SIZE + 1];
}	t_cmd;

t_cmd	*ft_init_struct(void)
{
	t_cmd	*cmd_tree;

	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
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

void	update_fd(t_cmd *tree)
{
	t_cmd	*temp;

	if (!tree)
		return ;
	temp = tree;
	while (temp)
	{
		if (temp->file_name == NULL)
		{
			if (!temp->fd_in)
				temp->fd_in = -1;
			if (!temp->fd_out)
				temp->fd_out = -1;
		}
		temp->pid = 0;
		if (ft_strcmp(temp->cmd[0], "echo") == 0)
		{
			if (ft_strcmp(temp->cmd[1], "-n") == 0)
				temp->token = 'n';
			else
				temp->token = 'e';
		}
		temp = temp->next;
	}
	tree = temp;
}


void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int *exit_status)
{
	t_cmd	*temp;
	int		i;

	if (!cmd || !*cmd)
		return ;
	temp = *cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			if (find_dollar_sign(temp, temp->cmd[i]))
				split_on_dollar(&temp->cmd[i], env, exit_status);
			i++;
		}
		temp = temp->next;
	}
}

void split_on_dollar(char **s, t_env *env, int *exit_status)
{
	char	**arr;
	char	*temp;
	char	*new_str;
	int		count;
	int		i;

	i = 0;
	new_str = NULL;
	count = 0;
	if (**s == '$')
	{
		temp = find_and_substitute(*s, env, exit_status);
		if (!temp)
			return ;
		*s = temp;
	}
	else
	{
		arr = ft_split(*s, '$');
		if (!arr)
			return ;
		count = ft_count(arr);
		while (arr[i + 1] != NULL)
		{
			temp = find_and_substitute(arr[i + 1], env, exit_status);
			if (!temp)
			{
				free_memory(arr);
				return ;
			}
			if (new_str == NULL)
			{
				new_str = ft_strjoin(arr[i], temp);
				if (!new_str)
				{
					free_memory(arr);
					free (temp);
					return ;
				}
			}
			else
			{
				new_str = ft_strjoin(new_str, temp);	
				if (!new_str)
				{
					free_memory(arr);
					free(new_str);
					free (temp);
					return ;
				}
			}
			free(temp);
			i++;
		}
		*s = new_str;
		free(new_str);
	}
}

char	*find_and_substitute(char *s, t_env *env, int *exit_status)
{
	char	*string;
	char	*temp;
	char	*temp1;

	temp = s;
	temp1 = move_past_dollar(temp);
	string = ft_variable(temp1, env, exit_status);
	if (string && *string != '\0')
		temp = string;
	else
		free (string);
	return (temp);
}
int	ft_find_environ_name(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=' && s[i] != '\n')
		i++;
	return (i);
}

int	find_dollar_sign(t_cmd *cmd, char *s)
{
	t_cmd	*temp;

	temp = cmd;
	while (*s != '\0' && *s != '$')
		s++;
	if (*s == '$')
	{
		if (!ft_strcmp((s + 1), "?"))
			temp->token_env = '?';
		return (1);
	}
	return (0);
}

char	*find_substitution(t_env *env, char *s, size_t cmd_len)
{
	t_env	*temp;
	size_t	var_len;
	char	*var_exp;

	temp = env;
	var_exp = NULL;
	var_len = 0;
	while (temp)
	{
		var_len = ft_find_environ_name(temp->cmd_env);
		if (ft_strncmp(s, temp->cmd_env, cmd_len) == 0 && var_len == cmd_len)
		{
			var_exp = temp->cmd_env + var_len + 1;
			break ;
		}
		temp = temp->next;
	}
	return (var_exp);
}

char	*ft_variable(char *s, t_env *env, int *exit_status)
{
	size_t	cmd_len;
	char	*result;
	char	*var_exp;

	var_exp = NULL;
	result = NULL;
	if (*(s) == '?')
	{
		result = ft_itoa(*exit_status);
		return (result);
	}
	cmd_len = strlen(s);
	var_exp = find_substitution(env, s, cmd_len);
	if (var_exp == NULL)
		return (ft_strdup(""));
	result = ft_strjoin(var_exp, s + cmd_len);
	if (!result)
		return (NULL);
	free (s);
	return (result);
}

char	*move_past_dollar(char *s)
{
	char	*str;

	if (!s || *s != '$')
		return (s);
	str = s + 1;
	return (str);		
}

void	parse_for_cmds(t_cmd **cmd, char *s)
{
	int		index;

	if (!s)
		return ;
	index = 0;
	s = check_for_quotes(s);
	parse_for_pipe(&s, cmd, 0, &index);
	update_fd(*cmd);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
//	restore_pipes_and_spaces(*cmd);
	if (*s != '\0')
		error_general("check syntax");
}

int	check_for_hanging_pipes(char *s)
{
	int	pipe_found;

	pipe_found = 0;
	while (*s)
	{
		if (*s == '|')
		{
			pipe_found = !pipe_found;
			s++;
			while (*s && is_whitespace(*s))
				s++;
			if (!*s && pipe_found)
			{
				perror("hanging pipe found, check syntax");
				return (1);
			}
		}
		s++;
	}
	return (0);
}

char	*check_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;

	if (!s)
		return (NULL);
	in_single = 0;
	in_double = 0;
	temp = s;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != temp[-1] && (*temp - 1) != '\\' \
			&& !in_double)
			in_single = !in_single;
		else if (*temp == '\"' && (*temp - 1) != temp[-1] && \
			(*temp - 1) != '\\' && !in_single)
			in_double = !in_double;
		else if ((*temp == '|' || *temp == ' ' || *temp == '<' || \
			*temp == '>' || *temp == '$') && (in_single || in_double))
			ft_replace(temp);
		temp++;
	}
	if (in_single || in_double)
		error_general("open quotes found, can't parse");
	return (s);
}

char	ft_replace(char *c)
{
	if (*c == '|')
		*c = '\xFD';
	else if (*c == ' ')
		*c = '\xFE';
	else if (*c == '<')
		*c = '\xD1';
	else if (*c == '>')
		*c = '\xA8';
	else if (*c == '$')
		*c = '\xAC';
	return (*c);
}
void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, int *index)
{
	t_cmd	*temp;
	t_cmd	*temp2;

	temp2 = NULL;
	if (!**str || !str)
		return ;
	if (prev_pipe == 0)
	{
		temp = parse_exec_cmds(str);
		if (!temp)
			error_general("parse exec failed");
		temp->index = *index;
		m_lstadd_back(cmd, temp);
	}
	(*index)++;
	if (check_next_char(str, '|'))
	{
		find_tokens(str, NULL);
		temp2 = parse_exec_cmds(str);
		temp2->index = *index;
		m_lstadd_back(cmd, temp2);
		parse_for_pipe(str, cmd, 1, index);
	}
}

void	restore_pipes_and_spaces(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	if (!cmd)
		return ;
	temp = cmd;
	while (temp)
	{
		i = 0;
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
			*(s) = '|';
		else if (*s == '\xFE')
			*(s) = ' ';
		else if (*s == '\xD1')
			*(s) = '<';
		else if (*s == '\xA8')
			*(s) = '>';
		else if (*s == '\xAC')
			*(s) = '$';
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

t_cmd	*init_exec_cmds(t_cmd *cmd_tree, char **s, char *non_token)
{
	int		i;
	int		token;
//	char	*temp;

	i = 0;
	token = 0;
//	temp = NULL;
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
		if (token == 0)
			break ;
		cmd_tree->token = token;
		cmd_tree->cmd[i] = non_token;
		if (!cmd_tree->cmd[i])
		{
			free_memory(s);
			free (non_token);
			return (NULL);
		}
		parse_line(cmd_tree->cmd[i]);
//		cmd_tree->cmd[i] = check_quotes(cmd_tree->cmd[i]);
		check_quotes(cmd_tree->cmd[i]);
		check_in_cmd_array_for_quotes(cmd_tree->cmd[i]);
//		cmd_tree->cmd[i] 
//		free (temp);
		i++;
		cmd_tree = parse_for_redirections(cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	return (cmd_tree);
}

t_cmd	*parse_exec_cmds(char **s)
{
	t_cmd	*cmd_tree;
	char	*non_token;

	non_token = NULL;
	cmd_tree = ft_init_struct();
	if (!cmd_tree)
		return (NULL);
	cmd_tree = parse_for_redirections(cmd_tree, s);
	if (!cmd_tree)
		return (NULL);
	cmd_tree = init_exec_cmds(cmd_tree, s, non_token);
	if (!cmd_tree)
	{
		ft_free_cmd_struct(cmd_tree);
		return (NULL);
	}
	return (cmd_tree);
}

void	remove_quotes(char *str)
{
	char	*src;
	char	*dst;
	
	src = str;
	dst = str;
	while (*src)
	{
		if (*src == '\'' || *src == '\"')
		{
			src++;
			continue ;
		}
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
//	return (dst);
}

void	check_in_cmd_array_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;

	if (!s)
		return ;
	in_single = 0;
	in_double = 0;
	temp = s;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != temp[-1] && (*temp - 1) != '\\' \
			&& !in_double)
			in_single++;
		else if (*temp == '\"' && (*temp - 1) != temp[-1] && \
			(*temp - 1) != '\\' && !in_single)
			in_double++;
		temp++;
	}
	if (in_single % 2 == 0 && in_double % 2 == 0)
		remove_quotes(s);
//	return (s);
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

int	is_token(char s)
{
	char	*tokens;

	tokens = "|<>";//()";
	if (ft_strchr(tokens, s))
		return (1);
	return (0);
}

int	is_whitespace(char s)
{
	char	*whitespace;

	whitespace = " \n\t\r\v";
	if (ft_strchr(whitespace, s))
		return (1);
	return (0);
}

//iterates through any whitespaces found before cmd/token
//boolean, returns 1 if true (if next char is a token) and 0 for false
int	check_next_char(char **s, char token)
{
	char	*temp;

	if (!*s)
		return (0);
	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	*s = temp;
	if (**s != '\0' && **s == token)
		return (1);
	return (0);
}
int	find_delimiter(char *s1, char *delim)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && delim[j] != '\0' && s1[i] == delim[j])
	{
		i++;
		j++;
	}
	if (delim[j] == '\0')
		return (1);
	return (0);
}

/*char	*check_quotes(char *s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[0] == s[len - 1])
		{
			temp = (char *)ft_calloc(len - 1, sizeof(char));
			if (!temp)
				return (NULL);
			while (i < len - 2)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
			ft_strcpy(s, temp);
			free (temp);
		}
	}
	return (s);
}*/

/*void	check_quotes(char *s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			temp = (char *)ft_calloc(len, sizeof(char));
			if (!temp)
				return ;
			while (i < len - 2)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
		}
	}
	s = temp;
	free (temp);
}*/

/*void	check_echo_and_quotes(t_cmd *cmd)
{}*/

void	check_quotes_single(char *s)
{
	size_t	i;
	size_t	len;
	size_t	new_len;
	char	*temp;

	len = ft_strlen(s);
	if (!s || len < 2)
		return ;
	i = 0;
	new_len = 0;
	if ((s[0] == '\'' && s[len - 1] == '\''))
	{
		if (s[i] == s[len - 1])
		{
			new_len = len - 2;
			temp = (char *)ft_calloc(new_len + 1, sizeof(char));
			if (!temp)
				return ;
			while (i < new_len)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
			ft_strcpy(s, temp);
			free(temp);
		}
	}
}

void	check_quotes_double(char *s)
{
	size_t	i;
	size_t	len;
	size_t	new_len;
	char	*temp;

	len = ft_strlen(s);
	if (!s || len < 2)
		return ;
	i = 0;
	new_len = 0;
	if ((s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			new_len = len - 2;
			temp = (char *)ft_calloc(new_len + 1, sizeof(char));
			if (!temp)
				return ;
			while (i < new_len)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
			ft_strcpy(s, temp);
			ft_restore(s);
			free(temp);
		}
	}
}
void	check_quotes(char *s)
{
	check_quotes_double(s);
	check_quotes_single(s);
}

int	g_signal;

void	print_stack(t_cmd *root)
{
	t_cmd	*temp;

	temp = root;
	while (temp != NULL)
	{
		printf("\nnode[%d]\n", temp->index);
		printf("fd_in: %d\n", temp->fd_in);
		printf("fd_out: %d\n", temp->fd_out);
		printf("file_name: %s\n", temp->file_name);
		printf("token: %c\n", temp->token);
		printf("delimiter: %s\n", temp->heredoc_delimiter);
		printf("token_env: %d\n", temp->token_env);
//		for (int i = 0; i < MAX_CONTENT_SIZE && temp->heredoc_content[i] != NULL; i++)
//		{
//			printf("heredoc content [%d]: %s\n", i, temp->heredoc_content[i]);
//		}
//		printf("node->data: %d\n", root-> data);
		for (int i = 0; i < MAXARGS && temp->cmd[i] != NULL; i++)
		{
			printf("cmd[%d]: %s\n", i, temp->cmd[i]);
		}
		temp = temp -> next;
	}
}

void	ft_execute(char *line, t_cmd **list, t_env **env_list, int *exit_status)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	parse_for_cmds(list, line);
	print_stack(*list);
	parse_cmds_for_expansions(list, *env_list, exit_status);
	restore_pipes_and_spaces(*list);
	printf("\nafter expansions and restoration\n");
	print_stack(*list);
	*exit_status = ft_executor(*list, env_list);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

char	*read_command(t_cmd *list, t_env **env_list, int *exit_status)
{
	char	*line;

	while (1)
	{
		ft_init_signals();
		line = readline("minishell: ");
		if (!line)
		{
			ft_free_env_list(env_list);
			printf("exit\n");
			exit(0);
		}
		while (*line != '\0' && is_whitespace(*line))
			line++;
		if (*line == '\0')
			break ;
		else if (check_for_hanging_pipes(line) == 0)
		{
			add_history(line);
			ft_execute(line, &list, env_list, exit_status);
			list = NULL;
			return (line);
		}
	}
	return (line);
}


void	handle_exit(t_env *env_list, char *line)
{
	rl_clear_history();
	free(line);
	ft_free_env_list(&env_list);
}

int	main(int argc, char **argv, char **env)
{
	static char	*line;
	t_cmd		*list;
	t_env		*env_list;
	int			exit_status;

	(void)argc;
	(void)argv;
	g_signal = 0;
	line = NULL;
	list = NULL;
	exit_status = 0;
	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);
	}
	if (!env)
		return (0);
	env_list = fill_env_struct(env);
	while (1)
		line = read_command(list, &env_list, &exit_status);
	handle_exit(env_list, line);
	free(list);
	list = NULL;
	return (exit_status);
}
