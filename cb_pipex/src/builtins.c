/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:22:32 by chbuerge          #+#    #+#             */
/*   Updated: 2024/03/28 10:56:57 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../libft/libft.h"
#include "../../minishell.h"

/*
** echo -n
** displays text or variables to the terminal or to files
** -n suppress the newline at the end that echo usually adds
** -n is optional, so we need to check for it
*/
void	ft_echo(char **input)
{
	//where to write it? terminal or file is the question
	size_t	i;
	int		len;
	int		flag;
	// 1 to skip echo? or different
	i = 1;
	flag = 0;
	// only works when I put "echo -n" in qoutes currently
	if (ft_strncmp("echo -n", input[1], 7) == 0)
		flag = 1;
	printf("flag: %d\n", flag);
	if (flag == 1)
		i = 2;
	else
		i = 2;
	while(input[i])
	{
		len = ft_strlen(input[i]);
		write(1, input[i], len);
		if (input[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (flag != 1)
		write(1, "\n", 1);
}

/*
** cd -> change directory (only rel or absolut path)
** change the current working directory
** if no dir is specified it goes to HOME
** chdir(const char *path), changes directory of calling process to dir specified
** getenv()
*/


// void	ft_cd(char *directory)
// {
// 	// if input after cd is NULL
// 	// if (chdir(getenv("HOME")) != 0)
// 		// handle error
// 	// else (try change dir)
// 		// if (chdir(input[xyz]) != 0))
// 			//handle error
// 	if(chdir("test") == -1)
// 		write(1, "error\n", 6);
// }

/*
** pwd (with no options)-> Printf Working Directory
** outputs the full pathname of the current working directory,
** which is the dir you are currently in within the filesystem hierarchy
*/
void	ft_pwd(char **environment)
{
	size_t	i;
	char *pwd;

	i = 0;
	pwd = NULL;
	while(environment[i])
	{
		if(ft_strncmp("PWD", environment[i], 3) == 0)
			pwd = environment[i];
		i++;
	}
	if (!pwd)
	{
		//handle error
	}
	printf("%s\n", pwd + 4);
}


// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// receive main struct as argument
void	ft_env(t_cmd *cmd)
{
	t_env *current = cmd->m_env;
	while(current)
	{
		ft_printf("%s\n", current->cmd_env);
		current = current->next;
	}
}


// ◦ exit with no options


int main (int argc, char **argv, char **env)
{
	//ft_pwd(env);
	//int i = 0;
	// while(argv[i])
	// {
	//	ft_echo(argv);
		// i++;
	// }
	// printf("directory: %s\n", argv[2]);
	// ft_cd(argv[2]);
	 char s[100];
	    printf("%s\n", getcwd(s, 100));
	chdir("test");
	    printf("%s\n", getcwd(s, 100));
	return (0);
}


// int main()
// {
//     char s[100];

//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));

//     // using the command
//     chdir("..");

//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));

//     // after chdir is executed
//     return 0;
// }
