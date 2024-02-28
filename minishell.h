/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:57:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/02/28 14:08:17 by kbolon           ###   ########.fr       */
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
# define PIPE
# define DELIMITER "|<>&()"

typedef struct s_type
{
	int	type;
}	t_type;

typedef struct s_exec
{
	int		type;
	char	*cmd[MAXARGS];
	char	*options[MAXARGS];
}	t_exec;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
}	t_redir;

typedef struct	s_cmd
{
	int		type;
	t_type	*left;
	t_type	*right;
}	t_cmd;



#endif