
# include <stdio.h>

//# include <readline/readline.h>
//# include <readline/history.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
//# include <fcntl.h>
//# include "libft/libft.h"

typedef struct s_exp t_exp;
void	parse_string(char *s);
void ft_find_var_declarations(char **s, t_exp **exp);
void	free_memory(char **arr);
char	**fill_array(char **arr, char **s, char *end);
int 	check_for_breaks(char **line) ;
void	quote_work(char *ptr, int *in_single, int *in_double);

typedef struct s_exp
{
	char	*exp_name;
	char	*exp_value;
	t_exp	*next;
}	t_exp;

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
char	*check_for_quotes(char *s)
{
	int		in_single;
	int		in_double;
	char	*ptr;
	char	*temp;

	if (!s)
	{
		printf("string is empty");
		return (NULL);
	}
	in_single = 0;
	in_double = 0;
	ptr = strdup(s);
	if (!ptr)
		return (NULL);
	quote_work(ptr, &in_single, &in_double);
	if (in_single || in_double)// == -1)
	{
		printf("open quotes found, can't parse\n");
		free (ptr);
		return (NULL);
	}
	return (ptr);
}

void	quote_work(char *ptr, int *in_single, int *in_double)
{
	char *temp;

	temp = ptr;
	while (*temp)
	{
		if (*temp == '\'' && (*temp - 1) != '\\' && !(*in_double))
			*in_single = !(*in_single);
		else if (*temp == '\"' && (*temp - 1) != '\\' && !(*in_single))
			*in_double = !(*in_double);
		else if (*temp == '|' && (in_single || in_double))
			*temp = '\xFD';
		else if (*temp == ' ' && (in_single || in_double))
			*temp =  '\xFE';
		temp++;
	}
}

void	check_for_var(char **line, t_exp **exp)
{
	int		i;
	char	*temp;

	i = 0;
	printf("temp after quotes: %s\n", temp);
	if (strchr(*line, '='))
	{
		while (*line && **line == ' ')
			(*line)++;
		if (**line == '\'' || **line == '\"')
		{
			printf("found quotes\n");
			return ;
		}
		while ((*line)[i] != '\0')
		{
			if ((*line)[i] == '=')
				break ;
			else if (is_token((*line)[i]))
			{
				printf("Token found before '='\n");
				return ;
			}
			i++;
		}
		ft_find_var_declarations(line, exp);
	}
//	parse_string(*line);
}

void	restore_exp(t_exp *exp)
//void	restore_pipes_and_spaces(t_cmd *cmd)
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
		if (*s == '\xFE')
			*s = ' ';
		s++;
	}
}

int check_for_breaks(char **line) //1 if space found
{
	char	*temp;

	temp = *line;
	while (*temp != '\0')
	{
		if (is_whitespace(*temp))//white space is found
		{
			temp = strchr(temp, ' ');
			(*line) = temp;
			return (1);
		}
		temp++;
	}
	return (0);
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

char	*check_quotes_var(char **s)
{
	size_t		len;
	char		*temp;
	size_t		i;

	i = 0;
	len = strlen(*s);
	temp = *s;
	if ((temp[0] == '\'' && temp[len - 1] == '\'') || (temp[0] == '\"' && temp[len - 1] == '\"'))
	{
		printf("quotes found\n");
		temp = (char *)malloc(sizeof(char) * (len - 2));
		if (!temp)
		{
			printf("problems mem alloc checkquotes");
			exit (1);
		}
		while (i < len - 2)
		{
			temp[i] = (*s)[i + 1];
			i++;
		}
		temp[i] = '\0';
		free(*s);
//		*s = strdup(temp);
//		free (temp);
	}
	return (temp);
}

char	**shell_split(char **s, char delimiter)
{
	char	**arr;
	char	*end;

	arr = (char **)calloc(3, sizeof(char *));
	if (!arr)
	{
		printf("problems allocating mem in export split\n");
		exit (1);
	}
	end = *s;
	while (*end != '\0' && *end != delimiter)
		end++;
	if (*end == delimiter)
		arr = fill_array(arr, s, end);
	return (arr);
}
/*char	*parse_line(char *arr)
{
	int		i;
	char	*temp;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i] != '\0' && (!is_whitespace(arr[i]) && !is_token(arr[i])))
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (arr[i] != '\0' && (!is_whitespace(arr[i]) && !is_token(arr[i])))
	{
		temp[i] = arr[i];
		i++;
	}
	temp[i] = '\0';
	free (arr);
	return (temp);
}*/

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

char	**fill_array(char **arr, char **s, char *end)
{
	char	*var_end;

	arr[0] = strndup(*s, end - *s);
	if (!arr[0])
	{
		free(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	var_end = end;
	while (*var_end != ' ' && *var_end != '\0' && *var_end != '|')
		var_end++;
	arr[1] =strdup(end + 1);
	if (!arr[1])
	{
		free (arr[0]);
		free (arr);
//		free_memory(arr);
		printf("problems mem alloc in ex split");
		exit (1);
	}
	*s = var_end;
	arr[2] = NULL;
	arr[1] = parse_line(arr[1]);
	arr[1] = check_quotes_var(&arr[1]);
	return (arr);
}

/*void	parse_string(char *s)
{
	char	*temp;

	temp = s;
	if (*temp != '\0')
	{
		while (*temp != '\0')
		{
			if (*temp != '\0' && is_whitespace(*temp))
			{
//				printf("open heredoc?\n");//check what bash returns
				return ;
			}
			temp++;
		}
	}
	s = temp;
}*/

void	ft_find_var_declarations(char **s, t_exp **exp)
{
	int		i;
	int		j;
	char	**arr;
	char	*temp;

	i = 0;
	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	while (temp[i] != '\0')
	{
		if (temp[i] == '=')
		{
			j = i - 1;
			while (j >= 0 && (temp[j] == ' '))
				j--;
			if (j >= 0)
			{
//				temp = check_quotes_var(&temp);//need to chek for quotes
				if (check_for_breaks(&temp) == 0)
				{
					printf("string after break: %s\n", temp);
					arr = shell_split(&temp, '=');
					if (!arr)
					{
						printf("problems splitting shell in exp finder\n");
						exit (0);
					}
					printf("string in shell split after split 2: %s\n", temp);
					*exp = insert_exp(*exp, arr[0], arr[1]);
					free(arr[0]);
					free(arr[1]);
					free(arr);
					*s = temp;
				}
				else
					*s = temp;
			}
		}
		i++;
	}
}
void	print_exp(t_exp *exp)
{
	t_exp	*temp;

	temp = exp;
	while (temp)
	{
		printf("exp name: %s\n", temp->exp_name);
		printf("exp value: %s\n", temp->exp_value);
		temp = temp->next;
	}
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
	// free(arr);
}

void	free_exp(t_exp *exp)
{
	t_exp	*temp;
	if (!exp)
		return ;
	while (exp)
	{
		temp = exp;
		if (temp->exp_name)
			free(temp->exp_name);
		if (temp->exp_value)
			free (temp->exp_value);
		exp = exp->next;
	}
	free (exp);
}

int	main()
{
	static char	*line = "  ccvar='123  ls'";
	t_exp	*exp;

	exp = NULL;
	line = check_for_quotes(line);
//	check_for_var(&line, &exp);
	printf("string in main: %s\n", line);
	printf("string len: %lu\n", strlen(line));
	if (strlen(line) > 0)

		printf("command found\n");
	if (exp)
		print_exp(exp);
	restore_exp(exp);
	printf(after\n);
	if (exp)
		print_exp(exp);
	free_exp(exp);
	if (exp)
		free (exp);
	return (0);
}
