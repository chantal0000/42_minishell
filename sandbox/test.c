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
//this function iterates through the nodes searching for the 
//'=' sign and then returns the string that matches.
char	*ft_find_environ_name(t_env *env)
{
	t_env	*temp;
	char	*s;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		s = temp->cmd_env;
		while (s[i] != '\0' && s[i] != '=' && s[i] != '\n')
			i++;
		temp = temp->next;
	}
	return (s);
}

int	find_dollar_sign(char *s)
{
	while (*s != '\0' && *s != '$')
		s++;
	if (*s == '$')
		return (1);
	return (0);
}

/*char	*ft_find_variable(char *s, t_env *env, int exit_status)
{
	char	*var_env;
	int		var_len;
	t_env	*temp;
	int		cmd_len;
	char	*result;
	char	*s_temp;

	var_env = NULL;
	cmd_len = 0;
	var_len = 0;
	s_temp = NULL;
	while (*s != '\0' && *s != '\n')
	{
		if (*s == '$')
		{
			printf("in ft_find_variable \n");
			printf("$ found!\n");
			if (*(s + 1) == '?')
			{
				result = strdup(ft_itoa(exit_status));
				return (result);
			}
			s++;
		}
		while (ft_isalnum(s[cmd_len]))
			cmd_len++;
		s++;
	}
	temp = env;
	while (temp)
	{
		s_temp = ft_find_environ_name(env);
		printf ("s_temp: %s\n", s_temp);
		var_len = ft_strlen(s_temp);
		if (ft_strncmp(s, s_temp, var_len) == 0 && var_len == cmd_len)
		{
//			if (temp->env_value != NULL)
			var_env = ft_strdup(temp->cmd_env + var_len);
			break ;
		}
		temp = temp->next;
	}
	if (var_env == NULL)
		return (ft_strdup(""));
	result = ft_strjoin(var_env, s + cmd_len);
	if (!result)
		return (NULL);
	return (result);
}*/

char	*parse_string_for_expansions(char *s, t_env *env, int exit_status)
{
	char	*temp;
	char	*str;
	int		i;
	char	*new_str;

	str = s;
	i = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			temp = &str[i];
//			temp = ft_find_variable(temp, env, exit_status);
			printf("ok\n");
			if (!temp)
				return (NULL);
			str = strndup(s, i);
			if (!str)
			{
				free(temp);
				return (NULL);
			}
			new_str = ft_strjoin(str, temp);
			free(temp);
			free(str);
			return (new_str);
		}
		i++;
	}
	return (s);
}

int	main()
{
	char	*s = "echo $PATH";

	printf("%d\n", find_dollar_sign(s));
	return (0);
}