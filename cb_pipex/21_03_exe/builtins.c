#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int	execute_cmd(char **env, char *cmd);
typedef struct s_exec t_exec;
typedef struct s_red t_red;

struct s_exec{
	// int		in;
	// init als -1
	int		fd_in;
	// only of the last output file
	int		fd_out;
	// example [ls] [-a]
	char	*cmd;
	//??
	t_exec	*prev;
	t_exec	*next;
    char **env;
    char *builtins_names[7];

	// save the env somewhere?
};
void    ft_init_bultins_names(t_exec *node);
/*
** 0 -> it's a builtin
*/
int ft_is_builtin(t_exec *node)
{
    int i;

    i = 0;
    ft_init_bultins_names(node);
    printf("in ft_is_builtin\n");
    while(i < 7)
    {
       // printf("in ft_is_builtin LOOP\n");
        // need ft_strcm
   //     printf("node->cmd: %s node->builtins_names: %s\n", node->cmd, node->builtins_names[i]);
        if(strcmp(node->cmd, node->builtins_names[i]) == 0)
            return (0);
        i++;
    }
    printf("END ft_is_builtin\n");
    return (1);
}

/*
** initialize builtins
*/
void    ft_init_bultins_names(t_exec *node)
{
    node->builtins_names[0] = "cd";
    node->builtins_names[1] = "echo";
    node->builtins_names[2] = "env";
    node->builtins_names[3] = "export";
    node->builtins_names[4] = "exit";
    node->builtins_names[5] = "pwd";
    node->builtins_names[6] = "unset";
}
