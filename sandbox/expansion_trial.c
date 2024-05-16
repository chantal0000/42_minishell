int	ft_find_environ_name(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=' && s[i] != '\n')
		i++;
	return (i);
}

char	*extract_variable_name(char *s)
{
	char	*end;

	if (!s || *s == '\0')
		return (NULL);
	end = NULL;
	while (valid_char(*end))
		end++;
	if (end == s)
		return (NULL);
	return (ft_strndup(s, end - s));
}

//function looks for $, returns 1 if found
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

int	valid_char(char c)
{
	return (isalnum(c) || (c == '_'));
}

int valid_variable(char *s)
{
	char	*temp;

	if (s == NULL || *s == '\0' || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	temp = s;
	while (*temp != '\0')
	{
		if (!valid_char(*temp))
			return (0);
		temp++;
	}
	return (1);
	
}

char *ft_strappend(char *orig, const char *add) {
    char *new_str = ft_strjoin(orig, add);
    free(orig);
    return new_str;
}

//function iterates through environment struct looking for a match
//when match is found, it copies everything after the '=' on from 
//environment
/*char	*find_substitution(t_env *env, char *s, size_t cmd_len)
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
}*/

char *find_substitution(t_env *env, char *s, size_t cmd_len) {
    t_env *temp = env;
    while (temp) {
        size_t var_len = ft_find_environ_name(temp->cmd_env);
        if (var_len == cmd_len && strncmp(s, temp->cmd_env, var_len) == 0) {
            return temp->cmd_env + var_len + 1;  // Return the value part of "VAR=value"
        }
        temp = temp->next;
    }
    return NULL;  // Not found
}

//this function copies the environment into the command array 
//it copies everything beyond the '='
/*char	*ft_variable(char *s, t_env *env, int *exit_status)
{
	size_t	cmd_len;
	char	*result;
	char	*var_exp;

	var_exp = NULL;
	result = NULL;
	if (*(s) == '?')
		return (ft_itoa(*exit_status));
	cmd_len = ft_strlen(s);
	var_exp = find_substitution(env, s, cmd_len);
	if (var_exp == NULL)
		return (ft_strdup(""));
	result = ft_strjoin(var_exp, s + cmd_len);
	if (!result)
		return (NULL);
	s = result;
	free (result);
	return (s);
}*/

char *ft_variable(char *s, t_env *env, int *exit_status) {
    // If the variable is special case `$?`, return its value immediately.
    if (*s == '?') {
        return ft_itoa(*exit_status);
    }

    // Calculate the length of the variable name.
    size_t cmd_len = ft_strlen(s);

    // Attempt to find the environment variable.
    char *variable_value = find_substitution(env, s, cmd_len);

    // If not found, return an empty string.
    if (variable_value == NULL) {
        return ft_strdup("");
    }

    // Return a copy of the found value to ensure memory safety.
    return ft_strdup(variable_value);
}

char	*move_past_dollar(char *s)
{
	char	*str;

	if (!s || *s != '$')
		return (s);
	str = s + 1;
	return (str);
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

/*void split_on_dollar(char **s, t_env *env, int *exit_status)
{
	char	**arr;
	char	*temp;
	char	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	if (**s == '$')
	{
		temp = find_and_substitute(*s, env, exit_status);
		if (temp)
			*s = temp;
	}
	else
	{
		arr = ft_split(*s, '$');
		if (!arr)
			return ;
		while (arr[i] != NULL)
		{
			temp = ft_run_sub(&arr[i], env, exit_status);
			if (!temp)
			{
				free_memory(arr);
				return ;
			}
			else
				new_str = make_new_str(arr, new_str, temp);
			free(temp);
			i++;
		}
		*s = new_str;
		free(new_str);
	}
}*/


void split_on_dollar(char **s, t_env *env, int *exit_status) {
    char *result = NULL;
    char *cur = *s;
    char *part_start = cur;
    char *temp;

    while (*cur) {
        if (*cur == '$') {
            // Copy text before '$'
            temp = strndup(part_start, cur - part_start);
            result = ft_strappend(result, temp);
            free(temp);

            char *var_name = extract_variable_name(cur + 1);
            if (var_name) {
                char *value = ft_variable(var_name, env, exit_status);
                result = ft_strappend(result, value);
                free(value);
                cur += strlen(var_name) + 1;  // Skip past the variable name
                free(var_name);
            } else {
                // No valid variable name, treat '$' as literal
                result = ft_strappend(result, "$");
                cur++;  // Move past the '$'
            }
            part_start = cur;  // Update the start of the next part
        } else {
            cur++;
        }
    }

    // Append any remaining part of the string after the last '$'
    if (cur != part_start) {
        temp = strndup(part_start, cur - part_start);
        result = ft_strappend(result, temp);
        free(temp);
    }

    free(*s);  // Free the original string
    *s = result;  // Update the original string pointer to the new string
}

char	*ft_run_sub(char **arr, t_env *env, int *exit_status)
{
	char	*temp;
	char 	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	temp = find_and_substitute(arr[i + 1], env, exit_status);
	if (!temp)
	{
		free_memory(arr);
		return (NULL);
	}
	if (new_str == NULL)
	{
		new_str = ft_strjoin(arr[i], temp);
		if (!new_str)
		{
			free_memory(arr);
			free (temp);
			return (NULL);
		}
	}
	return (new_str);
}

char	*make_new_str(char **arr, char *new_str, char *temp)
{
	new_str = ft_strjoin(new_str, temp);
	if (!new_str)
	{
		free_memory(arr);
		free(new_str);
		free (temp);
		return (NULL);
	}
	return (new_str);
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


