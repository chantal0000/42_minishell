/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:22:32 by chbuerge          #+#    #+#             */
/*   Updated: 2024/02/29 18:19:05 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	size_t	j;
	int		len;
	int		flag;
	// 1 to scip echo? or different
	i = 1;
	flag = 0;
	if (ft_strncmp("echo -n", input[1], 7))
	{
		flag = 1;
	}
	while(input[i])
	{
		len = ft_strlen(input[i]);
		write(1, input[i], len);
		i++;
	}
	// add null terminator?
	if (flag != 1)
	{
		//...
	}
}

/*
** cd -> change directory (only rel or absolut path)
** change the current working directory
** if no dir is specified it goes to HOME
** chdir(const char *path), changes directory of calling process to dir specified
** getenv()
*/










void	ft_cd()
{
	// if input after cd is NULL
	// if (chdir(getenv("HOME")) != 0)
		// handle error
	// else (try change dir)
		// if (chdir(input[xyz] != 0))
			//handle error
}

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
// ◦ exit with no options


int main (int argc, char **argv, char **env)
{
	pwd(env);

	return (0);
}
