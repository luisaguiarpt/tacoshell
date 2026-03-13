#include "../incs/minishell.h"

int g_signal;

int main(int ac, char **av, char **ep)
{
	t_shell	shell;

	(void)ac;
	shell = init_shell(av, ep);
	eval_loop(&shell);
	exit_clean(&shell, EXIT_SUCCESS);
	return (0);
}

void	eval_loop(t_shell *shell)
{
	setup_signals();
	while (true)
	{
		if (!read_line(shell))
			continue ;
		lexer(shell);
		parser(shell);
		executor(shell);
		clean(shell);
	}
}

void	parser(t_shell *shell)
{
	check_syntax(shell);
	if (shell->syntax_error)
		return ;
	if (shell->tokens == NULL || (*shell->tokens)->type == TK_EOF)
		return ;
	shell->ast_root = create_ast(shell);
}

void	executor(t_shell *shell)
{
	if (shell->syntax_error)
		return ;
	if (shell->ast_root == NULL)
		return ;
	exec_control(shell->ast_root, shell);
}
