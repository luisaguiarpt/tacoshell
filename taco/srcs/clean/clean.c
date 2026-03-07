#include "../../incs/minishell.h"

void	exit_clean(t_shell *shell, int exit_code)
{
	if (shell->line)
		free(shell->line);
	if (shell->vars)
		clean_shell_vars(shell);
//	if (shell->lexer)
//		clean_lexer(shell);
//	if (shell->ast_root)
//		clean_ast(shell);
	exit(exit_code);
}

void	clean_shell_vars(t_shell *shell)
{
	t_variable	*var;
	t_variable	*tmp;

	var = *shell->vars;
	while (var)
	{
		tmp = var->next;
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		if (var->exportstr)
			free(var->exportstr);
		free(var);
		var = tmp;
	}
	free(shell->vars);
}
