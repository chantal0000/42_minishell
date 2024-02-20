/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/20 18:18:10 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main()
{
	char	*line;
	char	*s1;//check mine
	char	*s2;//check real
	char	*token;
	char	*token2;

	line = readline("kach-22: ");
	if (!line)
		return (0);
	s1 = strdup(line);
	s2 = strdup(line);
//	parse_quotes_and_pipes(s1);
	token = ft_strtok(s1, DELIMITER);
	printf("Mine\n");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, DELIMITER);
	}
//	parse_quotes_and_pipes(s2);
	printf("Real\n");
	token2 = ft_strtok(s2, DELIMITER);
	while (token2 != NULL)
	{
		printf("%s\n", token2);
		token = strtok(NULL, DELIMITER);
	}
	free(line);
	free(s1);
	free(s2);
	return (0);
}
