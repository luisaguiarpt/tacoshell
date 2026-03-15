/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:23:06 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:23:10 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*get_next_token(t_shell *shell)
{
	skip_space(shell->lexer);
	shell->lexer->start = shell->lexer->current;
	if (is_at_end(shell->lexer))
		return (new_token_lexer(shell, TK_EOF));
	if (is_op_metachar(peek(shell->lexer)))
		return (read_op_token(shell));
	else
		return (read_word_token(shell));
}

t_token	*read_word_token(t_shell *shell)
{
	t_lexer	*lx;
	char	c;

	lx = shell->lexer;
	c = peek(lx);
	while (!(is_metachar(peek(lx)) && lx->state == NEUTRAL) && !is_at_end(lx))
	{
		if (c == '\'' && lx->state == NEUTRAL)
			lx->state = IN_SQ;
		else if (c == '\'' && lx->state == IN_SQ)
			lx->state = NEUTRAL;
		if (c == '"' && lx->state == NEUTRAL)
			lx->state = IN_DQ;
		else if (c == '"' && lx->state == IN_DQ)
			lx->state = NEUTRAL;
		if (c == '$' && lx->state != IN_SQ)
			shell->lexer->has_dollar = true;
		c = advance(1, lx);
	}
	return (new_token_lexer(shell, TK_WORD));
}

t_token	*read_op_token(t_shell *shell)
{
	char	c;

	c = peek(shell->lexer);
	if (c == '<' && match('<', shell->lexer))
		return (advance(2, shell->lexer), new_token_lexer(shell, TK_HERE_DOC));
	else if (c == '<')
		return (advance(1, shell->lexer), new_token_lexer(shell, TK_REDIR_IN));
	if (c == '>' && match('>', shell->lexer))
		return (advance(2, shell->lexer), new_token_lexer(shell, TK_APPEND));
	else if (c == '>')
		return (advance(1, shell->lexer), new_token_lexer(shell, TK_REDIR_OUT));
	if (c == '|' && match('|', shell->lexer))
		return (advance(2, shell->lexer), new_token_lexer(shell, TK_OR));
	else if (c == '|')
		return (advance(1, shell->lexer), new_token_lexer(shell, TK_PIPE));
	if (c == '&' && match('&', shell->lexer))
		return (advance(2, shell->lexer), new_token_lexer(shell, TK_AND));
	else if (c == '&')
		return (advance(1, shell->lexer), new_token_lexer(shell, TK_AMPERSAND));
	if (c == ';' && match(';', shell->lexer))
		return (advance(2, shell->lexer), new_token_lexer(shell, TK_SEMI_SEMI));
	else if (c == ';')
		return (advance(1, shell->lexer), new_token_lexer(shell, TK_SEMI));
	else
		return (advance(1, shell->lexer), new_token_lexer(shell, TK_EOF));
}

void	init_lexer(t_shell *shell)
{
	shell->lexer = ft_calloc(1, sizeof(t_lexer));
	if (!shell->lexer)
		exit_clean(shell, EXIT_FAILURE);
	shell->lexer->start = shell->line;
	shell->lexer->current = shell->line;
	shell->lexer->shell = shell;
	shell->lexer->state = NEUTRAL;
	shell->lexer->has_dollar = false;
}
