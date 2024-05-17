/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:34:15 by chbuerge          #+#    #+#             */
/*   Updated: 2024/05/17 16:47:04 by chbuerge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** signals in process before there is any input
*/
void	ft_ctrl_c_signals(int sig)
{
	(void)sig;
	g_signal = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDERR_FILENO, "\n", 1);
	rl_redisplay();
}

/*
** Ctrl C -> SIGINT
** Ctrl \ -> SIGQUIT (SIG_IGN function)
*/
void	ft_init_signals(void)
{
	signal(SIGINT, ft_ctrl_c_signals);
	signal(SIGQUIT, SIG_IGN);
}

/*
************************************************************
** signals in process with input
** Ctrl C -> exit and nl
** Ctrl D -> nothing
** Ctrl \ -> quit
*/
void	ft_ctrl_c_signals_input(int sig)
{
	(void)sig;
	g_signal = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDERR_FILENO, "\n", 1);
}

void	ft_quit_signals_input(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDERR_FILENO, "Quit\n", 6);
}

/*
** Ctrl C -> SIGINT
** Ctrl \ -> SIGQUIT (SIG_IGN function)
*/
void	ft_init_signals_input(void)
{
	signal(SIGINT, ft_ctrl_c_signals_input);
	signal(SIGQUIT, ft_quit_signals_input);
}
/* SIGNALS IN HEREDOC
** CTRL C -> exits
** CTRL \ -> nothing
** CTRL D (which is not actually a signal) bash: warning: here-document
   at line 9 delimited by end-of-file (wanted `eof')
*/
void	ft_init_signals_heredoc(int sig)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	(void) sig;
	g_signal = 130;
	// exit(130);
}
