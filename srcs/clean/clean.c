/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:45:38 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 19:53:51 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	clean(t_shell *shell)
{
	shell->syntax_error = false;
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->lexer)
		clean_lexer(shell);
	if (shell->ast_root)
		clean_ast(shell);
}

void	exit_clean(t_shell *shell, int exit_code)
{
	if (shell->prompt)
		free(shell->prompt);
	if (shell->line)
		free(shell->line);
	if (shell->vars)
		clean_shell_vars(shell);
	if (shell->lexer)
		clean_lexer(shell);
	if (shell->ast_root)
		clean_ast(shell);
	if (shell->env_ptr)
		free_array(shell->env_ptr);
	restore_terminal_state(shell);
	if (shell->orig_termios)
		free(shell->orig_termios);
	exit(exit_code);
}

void	clean_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}

void	clean_ast(t_shell *shell)
{
	clean_ast_node(shell->ast_root);
	shell->ast_root = NULL;
}

void	clean_lexer(t_shell *shell)
{
	if (!shell->tokens)
		return ;
	free_tokens(shell->tokens);
	free(shell->tokens);
	shell->tokens = NULL;
	free(shell->lexer);
	shell->lexer = NULL;
}
