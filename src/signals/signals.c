/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbuerge <chbuerge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:34:15 by chbuerge          #+#    #+#             */
/*   Updated: 2024/04/26 19:35:00 by chbuerge         ###   ########.fr       */
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
void ft_init_signals()
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
	// rl_redisplay();
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
void ft_init_signals_input()
{
	signal(SIGINT, ft_ctrl_c_signals_input);
	signal(SIGQUIT, ft_quit_signals_input);
}
