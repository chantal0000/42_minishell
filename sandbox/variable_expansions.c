#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((strlen(s1) + strlen(s2)) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
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
	if (!head)
		return (new_node);
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	return (head);
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

//function returns 1 if a parsable '=' is found
//parsable means not in quotes or token found before '='
int	search_string_for_equal(char *s)
{
	char	*temp;
	int		i;

	i = 0;
	temp = s;
	while (is_whitespace(*temp))
		temp++;
	if (strchr(temp, '='))
	{
		while (temp[i] != '\0' && temp[i] != '=' && temp[i] != '\'' && \
			temp[i] != '\"' && !is_token(temp[i]))
			i++;
		if (temp[i] == '=')
			return (1);
	}
	return (0);
}

char	*find_name(char **s)
{
	int		i;
	char	*name;
	char	*temp;

	i = 0;
	temp = *s;
	while (*temp != '\0' && is_whitespace(*temp))
		temp++;
	while (temp[i] != '\0' && temp[i] != '=')
		i++;
	name = strndup(temp, i);
	if (!name)
		return (NULL);
	*s = &temp[i];
	return (name);
}

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
			temp = (char *)malloc(sizeof(char) * (len - 1));
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

char	*find_value(char **s)
{
	int		i;
	char	*temp;
	char	*value;

	temp = *s;
	i = 0;
	if (*temp == '=')
		temp++;
	while (temp[i] != '\0' && !is_token(temp[i]) && !is_whitespace(temp[i]))
		i++;
	value = strndup(temp, i);
	if (!value)
		return (NULL);
	value = check_quotes(value);
	if (!value)
		return (NULL);
	while (temp[i] != '\0' && !is_whitespace(temp[i]))
		i++;
	*s = &temp[i];
	return (value);
}

void	free_exp(t_exp **exp)
{
	t_exp	*current;
	t_exp	*next;

	current = *exp;
	while (current != NULL)
	{
		next = current->next;

		if (current->exp_name)
			free(current->exp_name);
		if (current->exp_value)
			free(current->exp_value);
		free(current);
		current = next;
	}

	*exp = NULL; // Set the original pointer to NULL after freeing all nodes
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

void	parse_for_expansions(t_exp **exp, char **s)
{
	char	*name;
	char	*value;

	if (search_string_for_equal(*s) == 1)
	{
		name = find_name(s);
		value = find_value(s);
		*exp = insert_exp(*exp, name, value);
		free (name);
		free (value);
	}
	else
		printf("= sign not parsable, try command\n");
}


/*char	*ft_var_name2(char *s, t_exp *exp)
{
	char	*var_exp;
	int		var_len;
	t_exp	*temp;
	int 	cmd_len;
	char	*str_temp;

	cmd_len = 0;
	var_len = 0;
	if (*s == '$')
		(s)++;
	while (s[cmd_len] != '\0' && !is_whitespace(s[cmd_len]))
		cmd_len++;
	temp = exp;
	var_exp = NULL;
	while (temp)
	{
		var_len = strlen(temp->exp_name);
		if (var_len == cmd_len)
		{
			if (strncmp(s, temp->exp_name, var_len) == 0)
			{
				if (temp->exp_value != NULL)
					var_exp = strdup(temp->exp_value);
				if (!var_exp)
					return (NULL);
			}
		}
		temp = temp->next;
	}
	if (var_exp == NULL)
		return (NULL);
	var_exp = ft_strjoin(var_exp, s + cmd_len);
	if (!var_exp)
		return (NULL);
	return (var_exp);
}*/

char *ft_var_name2(char *s, t_exp *exp) {
    char *var_exp = NULL;
    int var_len, cmd_len = 0;
    t_exp *temp;

    if (*s == '$')
        s++;  // Skip the '$'

    while (s[cmd_len] != '\0' && !is_whitespace(s[cmd_len]))
        cmd_len++;

    temp = exp;
    while (temp) {
        var_len = strlen(temp->exp_name);
        if (strncmp(s, temp->exp_name, var_len) == 0 && var_len == cmd_len) {
            if (temp->exp_value != NULL) {
                var_exp = strdup(temp->exp_value);  // Duplicate value
                break;  // Found the correct expansion, no need to continue
            }
        }
        temp = temp->next;
    }

    if (var_exp == NULL)
        return strdup("");  // Return an empty string to ensure consistency

    char *result = ft_strjoin(var_exp, s + cmd_len);
    free(var_exp);  // Free the duplicated string as it's no longer needed
    return result;
}

char	*parse_string_for_expansions(char *s, t_exp *exp)
{
	char	*temp;
	char	*str;
	int		i;
	int		len;
	char 	*new_str;

	str = s;
	i = 0;
	len = 0;
	new_str = NULL;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		temp = &str[i];
		temp = ft_var_name2(temp, exp);
		if (!temp)
			return (NULL);
		len = strlen(temp);
		str = strndup(s, i);
		if (!str)
		{
			free (temp);
			return (NULL);
		}
		new_str = ft_strjoin(str, temp);
		free (temp);
		free (str);
		return (new_str);
	}
	return (s);
}

int	main()
{
	char 	*t = "var=24";
	char	*s = "ba=12";
	char	*test = "this$ba  ls";
	t_exp	*exp;
	char	*name;


	exp = NULL;
	parse_for_expansions(&exp, &t);
	parse_for_expansions(&exp, &s);
	if (strlen(s))
		printf("items left in string, try command\n");
	name = ft_var_name2(test, exp);
	if (exp)
	{
		free_exp(&exp);
		free (exp);
	}
	free (name);
	return (0);
}
