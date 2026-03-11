#include "../../incs/minishell.h"

t_shell	init_shell(char **av, char **ep)
{
	t_shell	shell;

	set_shell_null(&shell);
	set_shell_debug(&shell, av);
	//init_shell_vars_ptr(&shell);
	shell.vars = init_shell_vars(&shell, ep);
	update_shlvl(&shell);
	return (shell);
}

void	set_shell_null(t_shell *shell)
{
	shell->prompt = NULL;
	shell->line = NULL;
	shell->vars = NULL;
	shell->lexer = NULL;
	shell->tokens = NULL;
	shell->ast_root = NULL;
	shell->env_ptr = NULL;
	shell->debug = 0;
	shell->syntax_error = 0;
	shell->exit_status = 0;
}
