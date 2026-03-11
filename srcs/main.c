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
		read_line(shell);
		lexer(shell);
		parser(shell);
		clean(shell);
	}
}

void	parser(t_shell *shell)
{
	shell->ast_root = create_ast(shell);
	exec_control(shell->ast_root, shell);
}
