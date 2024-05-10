/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:44:55 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/10 15:50:37 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
** pwd with no options
** print working directory

** The first parameter, NULL, indicates that the function should allocate
** memory dynamically to store the current working directory path.
** The second parameter, 0, indicates that the function should determine the
** size of the buffer needed automatically based on the length of the
** current working directory path.
*/

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("error in pwd\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
