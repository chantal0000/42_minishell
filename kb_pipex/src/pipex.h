/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:30:04 by kbolon            #+#    #+#             */
/*   Updated: 2023/11/01 11:28:34 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

char	*get_path(char *cmd, char **envp);
void	run_cmd(char *cmd, char **envp);
void	free_memory(char **free_my_paths);
void	child(char **argv, int *fd, char **envp);
void	parent(char **argv, int *fd, char **envp);
int		pipex(char **argv, char **envp);
char	*make_path(char **all_path, char **cmd_split);
void	error_message(char *str, int i, int *fd, int *fd2);
void	checkstring(char *s);

#endif
