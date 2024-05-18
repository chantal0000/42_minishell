/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 08:13:52 by kbolon            #+#    #+#             */
/*   Updated: 2024/05/18 08:13:59 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
