/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/20 18:23:17 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
//MACOS
//# include <editline/readline.h>
//Linux
# include <readline/readline.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define TOKEN_BUF 100
# define DELIMITER "|<>&()"

typedef struct s_token
{
	int				type;//number of type of command (EXEC, PIPE? etc)
	char			*name;//file including the executable
	struct s_token	*left;
	struct s_token	*right;
	char			end;//null character?
}	t_token;

char	*ft_strtok(char *str, char *delimiter);
void	restore_pipes(char *str);
void	parse_quotes_and_pipes(char *str);
void	split_cmds(char *cmd);

#endif