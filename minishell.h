/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/27 14:48:39 by kbolon           ###   ########.fr       */
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
# define DELIMITER "|<>()"

#define MAXARGS 20

typedef struct s_type
{
	int	type;
}	t_type;

typedef struct s_exec_cmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*arg_options[MAXARGS];
}	t_exec_cmd;

typedef struct s_redir_cmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
}	t_redir_cmd;

typedef struct	s_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_cmd;


#endif