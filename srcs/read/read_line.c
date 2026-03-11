#include "../incs/minishell.h"

bool	read_line(t_shell *shell)
{
	get_prompt(shell);
	shell->line = readline(shell->prompt);
	if (!shell->line)
	{
		write(1, "exit\n", 5);
		exit_clean(shell, EXIT_SUCCESS);
	}
	if (!*shell->line)
		return (false);
	if (*shell->line)
		add_history(shell->line);
	return (true);
}
