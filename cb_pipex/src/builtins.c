/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:22:32 by chbuerge          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:29 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

//◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
void	pwd(char **environment)
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
