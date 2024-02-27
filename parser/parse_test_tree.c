
#include "../minishell.h"

#define MAXARGS 10

typedef struct s_cmd 
{
	int	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*arg_options[MAXARGS];
}	t_exec_cmd;

typedef struct s_redir_cmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
}	t_redir_cmd;

typedef struct	s_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_cmd;


int	is_token(char *s)
{
	char	tokens;

	tokens = "|<>()";
	if (ft_strchr(tokens, *s))
		return (1);
	return (0);
}

int	is_whitespace(char *s)
{
	char	whitespace;

	whitespace = " \n\t\r\v";
	if (ft_strchr(whitespace, *s))
		return (1);
	return (0);
}

int	check_for_alligators(char *s)
{
	int	result;

	result = *s;
	if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			result = '+';
			s++;
		}
	}
	if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			result = '-';
			s++;
		}
	}
	return (result);
}

int	find_tokens(char **pstr, char *begtok, char *endtok, char **s_len)
{
	char	*s;
	int		result;

	s = pstr;
	while (begtok < s_len && is_whitespace(*s))//or can I do != '\0'?
		s++;
	if (begtok)//if something in begtok, update s pointer to it
		*begtok = s;
	result = *s;
	if (*s == '|' || *s == '(' || *s == ')')
		s++;
	result = check_for_alligators(s);
	else
	{
		result = 'a';
		while (*s < s_len && !is_whitespace(*s) && !is_token(*s))
			s++;
	}
	if (endtok)
		*endtok = s;
	while (s < s_len && is_whitespace(*s))
		s++;
	*pstr = s;
	return (result);
}

int	peek(char **pstr, char *s_len)//boolean, returns 1 if true and 0 for false
{
	char	*s;

	s = *pstr;
	while (s < s_len && is_whitespace(*s))
		s++;
	*pstr = s;
	if (*s && is_token(*s))
		return (1); //if next non-whitespace is a token, return true
	return (0);
}

struct cmd	*parse_cmd(char *s)//returns a pointer to the cmd tree it builds
{
	char	*s_len;
	t_cmd	*cmd;

	s_len = ft_strchr(s, '\0'); //find end of string, not sure if I need it
	cmd = parse_line(&s, s_len);
	peek(&s, s_len);
	if (s != s_len)//means we have stopped before end of string
	{
		printf("check syntax\n");
		return (1);//panic function here???
	}
	nul_terminate_cmds(cmd);
	return (cmd);
}


//When a struct cmd* is received, it points to a base structure with limited fields. 
//To manipulate extended fields in derived structures like struct exec_cmd or 
//struct redir_cmd, the pointer must be cast to the appropriate type. 
//This casting informs the compiler of the pointer's actual structure type, 
//enabling access to both base and extended fields.

//This approach facilitates polymorphism in C, enabling functions like 
//nul_terminate_cmds to operate on various command types through a 
//common interface. By examining the type field and casting accordingly, 
//the function ensures type safety while handling diverse command structures.

t_cmd	*nul_terminate_cmds(t_cmd *cmd)
{
	t_exec_cmd	*exec_cmd;
	t_cmd	*list_cmd;
	t_cmd	*pipe_cmd;
	t_redir_cmd	*redir_cmd;
	int			i;

	if(!cmd)
		return (0);
	i = 0;
	if (cmd->type == EXEC)
		exec_cmd = ft_exec_cmd(cmd);
	if (cmd->type == PIPE)
	{
		pipe_cmd = (t_cmd *)cmd;
		{
			nul_terminate_cmds(pipe_cmd->left);
			nul_terminate_cmds(pipe_cmd->right);
		}
	}
	if (cmd->type == REDIR)
	{
		redir_cmd = (t_redir_cmd *)cmd;
		nul_terminate_cmds(redir_cmd->cmd);
		redir_cmd->end_file = 0;
	}
	if (cmd->type == LIST)
	{
		list_cmd = (t_cmd *)cmd;
		nul_terminate_cmds(list_cmd->left);
		nul_terminate_cmds(list_cmd->right);
	}
	return (cmd);
}

t_exec_cmd	*ft_exec_cmd(t_cmd cmd)
{
	t_exec_cmd	*exec_cmd;
	int			i;

	if(!cmd)
		return (0);
	i = 0;
	exec_cmd = (t_exec_cmd *)cmd;
	while (exec_cmd->arg_options[i])
		i++;
	exec_cmd->arg_options[i] = 0;
	return (exec_cmd);
}
