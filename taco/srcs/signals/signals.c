#include "../incs/minishell.h"

void	handle_ctrl_c(t_shell *shell)
{
	shell->exit_status = 130;
	g_signal = 0;
	return ;
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

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	disable_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
}

void	restore_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
}
