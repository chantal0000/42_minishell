#include "../minishell.h"
#include "./../libft/libft.h"

typedef struct s_exp
{
	char	*exp_name;
	char	*exp_value;
	t_exp	*next;
}	t_exp;

t_exp	*init_exp_struct(void)
{
	void	*ptr;

	ptr = (void *)ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

void	m_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
//		new->prev = m_lstlast(*lst);
		new->next = NULL;
		m_lstlast(*lst)->next = new;
	}
	else
	{
		new->next = NULL;
//		new->prev = NULL;
		*lst = new;
	}
}

t_cmd	*m_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst -> next;
	return (lst);
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
	free(arr);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
	{
		*ptr++ = 0;
	}
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = (void *) malloc (nmemb * size);
	if (!p)
		return (0);
	ft_bzero(p, (nmemb * size));
	return (p);
}

/*static char	*ft_strchr(const char *s, int i)
{
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i == '\0')
		return ((char *)s);
	return (0);
}*/

/*static char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	strlen;

	if (!s)
		return (0);
	strlen = ft_strlen(s);
	if (start > strlen)
	{
		len = 0;
		start = strlen;
	}
	else if (start + len > strlen)
		len = strlen - start;
	ptr = (char *)malloc(len + 1 * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}*/

/*static char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	char	*ptr;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	ptr = ft_substr(s1, 0, i + 1);
	if (!ptr)
		return (0);
	return (ptr);
}*/

char	*check_quotes(char *s)
{
	size_t		i;
	size_t		len;
	char		*temp;

	i = 0;
	len = strlen(s);
	temp = s;
	if ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '\"' && s[len - 1] == '\"'))
	{
		if (s[i] == s[len - 1])
		{
			temp = (char *)malloc(sizeof(char) * len -2);
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

char	**export_split(char	*s)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)ft_calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	while (s[i] != '\0' && s[i] != '=')
		i++;
	arr[0] = ft_calloc(i + 1, sizeof(char));
	if (!arr[0])
	{
		printf("problems mem alloc in ex split");
		exit (1);
	}
	memcpy(arr[0], s, i);
	arr[0][i] = '\0';
	arr[1] = ft_calloc(strlen(s) - i + 1, sizeof(char));
	if (!arr[1])
	{
		free_memory(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	memcpy(arr[1], &s[i + 1], strlen(s) - i);
	arr[1][strlen(s) - 1] = '\0';
	arr[2] = NULL;
	check_quotes(arr[1]);
	return (arr);
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

t_cmd	*parse_exec_cmds(char **s)
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
	return (cmd_tree);
}

int	main(int argc, char **argv)
{
//	char	*s = "var=\"'==this'\"";
	char	**arr;

	arr = export_split(argv[1]);
	int	i = 0;
	printf("line to be parsed: %s\n", argv[1]);
	while (arr[i] != NULL)
	{
		printf("arr [%d]: %s\n", i, arr[i]);
		i++;
	}
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}