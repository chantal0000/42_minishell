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
				result = ft_strdup(ft_itoa(exit_status));
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
			temp = ft_find_variable(temp, env, exit_status);
			printf("ok\n");
			if (!temp)
				return (NULL);
			str = ft_strndup(s, i);
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


//void	parse_cmds_for_expansions(t_cmd **cmd, t_env *env, int exit_status)
void	parse_cmds_for_expansions(t_cmd **cmd)
{
	t_cmd	*temp;
	int		i;
	char	*string;

	if (!cmd)
		return ;
	temp = *cmd;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i] != NULL)
		{
			if (find_dollar_sign(temp->cmd[i]))
				string = ft_find_variable(temp->cmd[i], env, exit_status);
			printf("ok e\n");
//			printf("string in parse_cmds for exp: %s\n", string);
/*			if (string && *string != '\0')
			{
				free (temp->cmd[i]);
				temp->cmd[i] = string;
			}
			else
				free (string);*/
			i++;
		}
		temp = temp->next;
	}
}
