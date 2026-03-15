/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:56:59 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:57:00 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_shell	init_shell(char **av, char **ep)
{
	t_shell	shell;

	set_shell_null(&shell);
	set_shell_debug(&shell, av);
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

void	init_tokens_ptr(t_shell *shell)
{
	shell->tokens = ft_calloc(1, sizeof(t_token *));
	if (!shell->tokens)
		exit_clean(shell, EXIT_FAILURE);
}

void	init_shell_vars_ptr(t_shell *shell)
{
	shell->vars = ft_calloc(1, sizeof(t_variable *));
	if (!shell->vars)
		exit_clean(shell, EXIT_FAILURE);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
