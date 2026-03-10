#include "../incs/minishell.h"

bool	read_line(t_shell *shell, char *str)
{
	shell->line = readline(str);
	if (!shell->line)
	{
		write(1, "exit\n", 5);
		exit_clean(shell, EXIT_SUCCESS);
	}
	if (!shell->line)
		return (false);
	if (*shell->line)
		add_history(shell->line);
	return (true);
}
