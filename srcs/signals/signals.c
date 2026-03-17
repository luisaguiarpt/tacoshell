/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:54:52 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:54:53 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	handle_readline(t_shell *shell)
{
	if (g_signal != 0)
	{
		shell->exit_status = g_signal;
		g_signal = 0;
	}
}

void	handle_ctrl_c(int signo)
{
	(void)signo;
	g_signal = 130;
}

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_signal = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGINT, handle_sigint);
	}
}

void	handler_heredoc(int signo)
{
	(void)signo;
	g_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	//signal(SIGINT, handle_ctrl_c);
	//signal(SIGQUIT, SIG_IGN);
}

void	handle_backslash(int signo)
{
	(void)signo;
	g_signal = 131;
}

void	enable_child_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

void	disable_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGPIPE, SIG_DFL);
}
