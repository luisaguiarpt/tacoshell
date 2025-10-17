#include "tacoshell.h"

volatile sig_atomic_t	g_signal = 0;

void	handle_sigint(int	signo)
{
	(void)signo;
	g_signal = 1;
	write(1, "\n", 1);
}

void	handle_sigquit(int signo)
{
	(void)signo;
	write(1, "/b/b /b/b", 6);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
