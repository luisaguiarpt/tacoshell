/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:13 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:16:15 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

t_scanner	*init_scanner(t_core *core)
{
	t_scanner	*scanner;

	scanner = wr_calloc(1, sizeof(t_scanner), core);
	scanner->start = core->line;
	scanner->current = core->line;
	scanner->core = core;
	scanner->state = NEUTRAL;
	return (scanner);
}

t_token	scan_token(t_scanner *scanner)
{
	char		c;

	skip_space(scanner);
	scanner->start = scanner->current;
	if (is_at_end(scanner))
		return (create_token(EOF_TOK, scanner));
	c = peek(scanner);
	if (c == '|' || c == '<' || c == '>')
		return (scan_op(c, scanner));
	if (c == '(' || c == ')')
		return (error_token(ERROR_TOK_BR, scanner));
	if (c == ';' || c == '&')
		return (create_token(EOF_TOK, scanner));
	return (scan_word(scanner, c));
}

t_token	scan_op(char c, t_scanner *scanner)
{
	if (c == '<')
	{
		if (match('<', scanner))
			return (advance2(scanner), create_token(HERE_DOC, scanner));
		else
			return (advance(scanner), create_token(REDIR_IN, scanner));
	}
	if (c == '>')
	{
		if (match('>', scanner))
			return (advance2(scanner), create_token(APPEND, scanner));
		else
			return (advance(scanner), create_token(REDIR_OUT, scanner));
	}
	else
		return (advance(scanner), create_token(PIPE, scanner));
}
// Peek returns the current character
// Advance returns the current character and advances to the next character
// Match checks to see if the argument matches the current character, if so, advances to the next character
// is_at_end returns true if current character is \0

t_token scan_word(t_scanner *scanner, char c)
{
	while (!(is_metachar(peek(scanner)) && scanner->state == NEUTRAL) && !is_at_end(scanner))
	{
//		c = peek(scanner);
		if (c == '\'' && scanner->state == NEUTRAL)
			scanner->state = IN_SINGLE_QUOTES;
		else if (c == '\'' && scanner->state == IN_SINGLE_QUOTES)
			scanner->state = NEUTRAL;
		if (c == '"' && scanner->state == NEUTRAL)
			scanner->state = IN_DOUBLE_QUOTES;
		else if (c == '"' && scanner->state ==  IN_DOUBLE_QUOTES)
			scanner->state = NEUTRAL;
		if (scanner->current[1] == 0 && scanner->state == IN_SINGLE_QUOTES)
			return(error_token(ERROR_TOK_SQ, scanner));
		else if (scanner->current[1] == 0 && scanner->state == IN_DOUBLE_QUOTES)
			return(error_token(ERROR_TOK_DQ, scanner));
		c = advance(scanner);
	}
	return (create_token(WORD, scanner));
}

bool	is_at_end(t_scanner *scanner)
{
	return (*scanner->current == 0);
}
