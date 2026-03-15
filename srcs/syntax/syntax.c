/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:56:08 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:56:10 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_syntax(t_shell *shell)
{
	if (!shell->syntax_error)
		syntax_pipe_start(shell);
	if (!shell->syntax_error)
		syntax_pipe_end(shell);
	if (!shell->syntax_error)
		syntax_redirs(shell);
	if (!shell->syntax_error)
		syntax_operators(shell);
}

void	syntax_quotes(t_shell *shell, t_token *token)
{
	int		i;
	t_state	state;

	i = 0;
	state = NEUTRAL;
	while (token->word[i])
	{
		if (token->word[i] == '"' && state == NEUTRAL)
			state = IN_DQ;
		else if (token->word[i] == '"' && state == IN_DQ)
			state = NEUTRAL;
		else if (token->word[i] == '\'' && state == NEUTRAL)
			state = IN_SQ;
		else if (token->word[i] == '\'' && state == IN_SQ)
			state = NEUTRAL;
		i++;
	}
	if (state == IN_DQ)
		set_syntax_error_quotes(shell, "\"", 2);
	else if (state == IN_SQ)
		set_syntax_error_quotes(shell, "'", 2);
}

void	syntax_redirs(t_shell *shell)
{
	t_token	*token;

	token = *shell->tokens;
	while (token)
	{
		if (is_redir_operator(*token) && !is_word(*token->next))
		{
			set_syntax_error_tok(shell, token->next, 2);
			return ;
		}
		token = token->next;
	}
}

void	syntax_pipe_start(t_shell *shell)
{
	t_token	*head;

	head = *shell->tokens;
	if (head->type == TK_PIPE)
	{
		ft_printf_fd(STDERR_FILENO, ERRMSG_PIPE);
		shell->exit_status = 2;
		shell->syntax_error = true;
		return ;
	}
}

void	syntax_pipe_end(t_shell *shell)
{
	t_token	*last;

	last = last_token(shell);
	if (last->prev)
		last = last->prev;
	if (last->type == TK_PIPE)
	{
		ft_printf_fd(STDERR_FILENO, ERRMSG_PIPE);
		shell->exit_status = 2;
		shell->syntax_error = true;
		return ;
	}
}

void	syntax_operators(t_shell *shell)
{
	t_token	*head;

	head = *shell->tokens;
	if (is_token_operator(head))
		set_syntax_error_tok(shell, head, 2);
}
