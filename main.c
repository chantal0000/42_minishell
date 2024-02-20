/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:54:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/20 07:22:29 by kbolon           ###   ########.fr       */
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

	line = readline("minishell: ");
	if (!line)
		return (0);
	s1 = strdup(line);
	s2 = strdup(line);
//	parse_quotes_and_pipes(s1);
	token = ft_strtok(s1, DELIMETER);
	printf("Mine\n");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, DELIMITER);
	}
//	parse_quotes_and_pipes(s2);
	printf("Real\n");
	token2 = ft_strtok(s2, DELIMETER);
	while (token2 != NULL)
	{
		printf("%s\n", token2);
		token = strtok(NULL, DELIMETER);
	}
	free(line);
	free(s1);
	free(s2);
	return (0);
}
