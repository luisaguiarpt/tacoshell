/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:54:52 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:54:53 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	handler_heredoc(int signo)
{
	(void)signo;
	g_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
}

bool	check_heredoc_interrupt(t_shell *shell)
{
	if (g_signal != 0)
	{
		g_signal = 0;
		shell->exit_status = 130;
		shell->syntax_error = true;
		return (true);
	}
	return (false);
}

void	handle_readline(t_shell *shell)
{
	if (g_signal != 0)
	{
		shell->exit_status = g_signal;
		g_signal = 0;
	}
}
