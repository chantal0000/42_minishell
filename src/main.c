/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/21 16:09:14 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	char	*s1;
	char	*token;

	line = readline("kach-22: ");
	if (!line)
		return (0);
	s1 = ft_strdup(line);
	token = ft_strtok(s1, DELIMITER);
	printf("\nMine\n");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, DELIMITER);
	}
	free(line);
	free(s1);
	return (0);
}
