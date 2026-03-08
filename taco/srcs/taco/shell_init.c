#include "../../incs/minishell.h"

t_shell	init_shell(char **av, char **ep)
{
	t_shell	shell;

	set_shell_null(&shell);
	set_shell_debug(&shell, av);
	init_shell_vars_ptr(&shell);
	init_shell_vars(&shell, ep);
	return (shell);
}

void	set_shell_null(t_shell *shell)
{
	shell->line = NULL;
	shell->vars = NULL;
	shell->lexer = NULL;
	shell->tokens = NULL;
//	shell->ast_root = NULL;
	shell->debug = false;
	shell->exit_status = 0;
}
