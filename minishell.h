/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/19 10:41:28 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5

typef struct s_token
{
	int				*type;
	char			*str;
	struct s_token	*left;
	struct s_token	*right;
	char			char;//null character?
}	t_token;

void	makefile_check();

#endif