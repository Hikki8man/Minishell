/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_pap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:48 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/13 15:04:32 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sig_pap(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		*g_ptr = 1;
	}
}

/*
 * Remove ^C with termcaps and redisplay prompt
 * Ignore ^\ signal
 */
void	sig_pap_handler(void)
{
	struct termios	terminos;

	tcgetattr(0, &terminos);
	terminos.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminos);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_pap);
}
