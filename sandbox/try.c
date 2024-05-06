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

t_exp	*insert_exp(t_exp *head, char *name, char *value)
{
	t_exp	*new_node;
	t_exp	*temp;

	new_node = (t_exp *)calloc(1, sizeof(t_exp));
	if (!new_node)
		return (NULL);
	new_node->exp_name = strdup(name);
	new_node->exp_value = strdup(value);
	new_node->next = NULL;
	if(!head)
		return (new_node);
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (head);
}

void	parse_for_cmds(t_cmd **cmd, char *s)
{
	t_exp	*exp;

	exp = NULL;
	if (!s)
		return ;
	s = check_for_quotes(s);
	parse_for_pipe(&s, cmd, 0, exp);
	update_fd(*cmd);
	while (*s != '\0' && is_whitespace(*s))
		(*s)++;
	if (*s != '\0')
	{
		printf("check syntax\n");//check what bash returns
		return ;
	}
	restore_pipes_and_spaces(*cmd);
}

int	is_token(char s)
{
	char	*tokens;

	tokens = "|<>()";
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

	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	*s = temp;
	if (**s != '\0' && **s == token)
		return (1);
	return (0);
}

char	*check_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*temp;

	if (!s)
	{
		printf("string is empty");
		exit(1);
	}
	in_single = 0;
	in_double = 0;
	temp = s;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != '\\' && !in_double)
			in_single = !in_single;
		else if (*temp == '\"' && (*temp - 1) != '\\' && !in_single)
			in_double = !in_double;
		else if (*temp == '|' && (in_single || in_double))
			*temp = '\xFD';
		else if (*temp == ' ' && (in_single || in_double))
			*temp =  '\xFE';
		temp++;
	}
	if (in_single || in_double)// == -1)
	{
		printf("open quotes found, can't parse");
		exit (1);
	}
	return (s);
}

void	parse_for_pipe(char **str, t_cmd **cmd, int prev_pipe, t_exp *exp)
{
	t_cmd	*temp;
	t_cmd	*temp2;

	temp2 = NULL;
	if (!**str || !str)
		return ;
	if (prev_pipe == 0)
	{
		temp = parse_exec_cmds(str, exp);
		if (!temp)
			return ;
		m_lstadd_back(cmd, temp);
	}
	if (check_next_char(str, '|'))
	{
		find_tokens(str, NULL);
		temp2 = parse_exec_cmds(str, exp);
		m_lstadd_back(cmd, temp2);
		parse_for_pipe(str, cmd, 1, exp);
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
	cmd_tree = parse_for_redirections(cmd_tree, s);
	if (!cmd_tree)
		return (NULL);
	while (*s && !is_token(**s))
	{
		token = find_tokens(s, &non_token);
//		printf("non_token %s\n", non_token);
/*		if (ft_strchr(non_token, '='))
		{
			printf("variable declaration found\n");
//			if(ft_find_var_declarations(&cmd_tree))
//				token = find_tokens(s, &non_token);
		}*/
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
		i++;
		cmd_tree = parse_for_redirections(cmd_tree, s);
	}
	cmd_tree->cmd[i] = NULL;
	return (cmd_tree);
}

t_cmd	*parse_exec_cmds(char **s, t_exp *exp)
{
	t_cmd	*cmd_tree;
	char	*non_token;

	non_token = NULL;
	cmd_tree = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_tree)
	{
		printf("cmd_tree initiation in exec failed\n");
		exit (1);
	}
	cmd_tree = init_exec_cmds(s, non_token);
	if (!cmd_tree)
		free_cmdtree(cmd_tree);
	exp = ft_find_var_declarations (&cmd_tree, exp);
	cmd_tree = *ft_find_var_expansions(&cmd_tree, exp);
	if (!cmd_tree)
		free_cmdtree(cmd_tree);
	return (cmd_tree);
}

char	*check_quotes(char *s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	i = 0;
	len = ft_strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			temp = (char *)malloc(sizeof(char) * len - 2);
			if (!temp)
			{
				printf("problems mem alloc checkquotes");
				exit (1);
			}
			while (i < len - 2)
			{
				temp[i] = s[i + 1];
				i++;
			}
			temp[i] = '\0';
		}
	}
	return (temp);
}

char	**shell_split(char *s, char c)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	while (s[i] != '\0' && s[i] != c)
		i++;
	arr[0] = strndup(s, i);
	if (!arr[0])
	{
		printf("problems mem alloc in ex split");
		exit (1);
	}
	arr[1] = strndup(s + i + 1, strlen(s) - i - 1);
	if (!arr[1])
	{
//		free_memory(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	arr[2] = NULL;
	check_quotes(arr[1]);
	return (arr);
}

t_exp	*ft_find_var_declarations(t_cmd **cmd, t_exp *exp)
{
	int		i;
	char	**arr;
	t_cmd	**temp;

	i = 0;
	temp = cmd;
	while (temp[0]->cmd[0][i] != '\0')
	{
		if (temp[0]->cmd[0][i] == '=')
		{
			arr = shell_split(temp[0]->cmd[0], '=');
			if (!arr)
			{
				printf("problems splitting shell in exp finder\n");
				arr = NULL;
			}
			exp = insert_exp(exp, arr[0], arr[1]);
			temp[0]->token = '$';
			temp[0]->cmd[0] = "";
		}
		i++;
	}
	cmd = temp;
	return (exp);
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
			if (ft_strchr((*temp)->cmd[i], '$'))
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
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			i++;
			if (s[i] == '?')
				printf("? found\n");
				//deal with ? here
//			else if (s[i] == '\'' || s[i] == '\"' || s[i] == ' ')
//				continue ;
		}
		else if (s[i] ==  '$' && (s[i + 1] == '\'' || s[i + 1] == '\"' || s[i + 1] == ' ' || s[i + 1] == '$'))
			continue ;
		else
			s = apply_expansion_magic(s, &i, exp);
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
		if (s[*i] == '$' && (ft_isalnum(s[*i + 1]) || s[*i + 1] == '_'))
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
	temp = exp;
	name_len = 0;
	var_exp = NULL;
	while(*name && (ft_isalnum(*name) || *name == '_'))//goes to end of var name
		name++;
	while (temp)
	{
		if (ft_strcmp(name, temp->exp_name) == 0)
		{
			if (temp->exp_value != NULL)
				var_exp = ft_strjoin(var_exp, temp->exp_value);
			else
			 	var_exp = ft_strjoin(var_exp, "");
			if (!var_exp)
				return (NULL);
		}
		temp = temp->next;
	}
	name_len = ft_strlen(name);
	var_exp = ft_strjoin(var_exp, s + name_len);
	if (!var_exp)
		return (NULL);
	return (var_exp);
}
int	main(int argc, char **argv, char **env)
{
	static char	*line;
//	char	*line = " grep lady < infile.txt | nl";
	t_cmd	*list;
	t_env	*env_list;
	int original_stdout = dup(STDOUT_FILENO);
	int original_stdin = dup(STDIN_FILENO);
//	int exit_status = 0;

	(void)argc;
	(void)argv;
	g_signal = 0;
	list = NULL;
	if (argc != 1)
	{
		write(STDERR_FILENO, "invalid arguments: ambiguous redirect\n", 38);
		exit(1);//is this the right error code?
	}
	if (!env)
		return (0);
	env_list = fill_env_struct(env);
	while (1)
	{

		ft_init_signals();
		line = readline("minishell: ");
		// this is basically ctrl D
		if (!line)
		{
			// free memory
			// free(env_list);
			while (env_list != NULL)
			{
			t_env *next = env_list->next;
			free(env_list);
			env_list = next;
			}
			printf("exit\n");
			exit(0);
		}
//		printf("line to be parsed: %s\n", line);
		add_history(line);
		parse_for_cmds(&list, line);//need to add envp
		print_stack(list);
		if (!list)
		{
			free(line);
			return (0);
		}
		ft_executor(list, env_list);
		dup2(original_stdin, STDIN_FILENO);
		// close(original_stdin);
		dup2(original_stdout, STDOUT_FILENO);
		// close(original_stdout);
		list = NULL; // here needs to be freed
		free_cmdtree(list);
	}
	HIST_ENTRY *entry = history_get(where_history());
	printf("%s\n", entry->line);
//	exit_status = ft_executor(list);
	free(line);
	free_cmdtree(list);
//	return (exit_status);
	free(line);
	return (0);
}