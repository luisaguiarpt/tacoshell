#include "../../incs/minishell.h"

void	check_syntax(t_shell *shell)
{
	syntax_pipe_start(shell);

	(void)shell;
}

void	syntax_pipe_start(t_shell *shell)
{
	t_token	*head;

	head = *shell->tokens;
	if (head->type == TK_PIPE)
	{
		ft_printf_fd(STDERR_FILENO, ERR_MSG_PIPE);
		shell->exit_status = true;
		shell->syntax_error = true;
		return ;
	}
}
