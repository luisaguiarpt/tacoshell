#include "../incs/minishell.h"

int g_signal;

int main(int ac, char **av, char **ep)
{
	t_shell	shell;

	(void)ac;
	shell = init_shell(av, ep);
	exit_clean(&shell, EXIT_SUCCESS);
	return (0);
}
