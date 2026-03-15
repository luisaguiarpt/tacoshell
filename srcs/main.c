/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:40:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/11 16:40:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_signal;

int	main(int ac, char **av, char **ep)
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

void	lexer(t_shell *shell)
{
	t_token	*token;

	init_lexer(shell);
	init_tokens_ptr(shell);
	while (true)
	{
		shell->lexer->has_dollar = false;
		token = get_next_token(shell);
		syntax_quotes(shell, token);
		append_token(shell, token);
		set_heredoc_delimiter(shell, token);
		expansion(shell, &token);
		if (token && token->type == TK_EOF)
			break ;
	}
	if (shell->debug)
		print_tokens(shell);
}

void	parser(t_shell *shell)
{
	check_syntax(shell);
	if (shell->syntax_error)
		return ;
	if (shell->tokens == NULL || (*shell->tokens)->type == TK_EOF)
		return ;
	shell->ast_root = create_ast(shell);
	if (shell->debug & PRT_AST)
		debug_ast(shell->ast_root);
}

void	executor(t_shell *shell)
{
	if (shell->syntax_error)
		return ;
	if (shell->ast_root == NULL)
		return ;
	exec_control(shell->ast_root, shell);
}
