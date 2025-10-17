#include "tacoshell.h"

t_token	scan_token(t_scanner *scanner)
{
	char		c;

	skip_space(scanner);
	scanner->start = scanner->current;
	if (is_at_end(scanner))
		return (create_token(EOF_TOK, scanner));
	c = advance(scanner);
	return (scan1(c, scanner));
}

t_token	scan1(char c, t_scanner *scanner)
{
	if (c == '|')
		return (create_token(PIPE, scanner));
	if (c == '$')
	{
		while (peek(scanner) != ' ' && !is_at_end(scanner))
			advance(scanner);
		return (create_token(DOLLAR, scanner));
	}
	return (scan2(c, scanner));
}

t_token	scan2(char c, t_scanner *scanner)
{
	if (c == '<')
	{
		if (match('<', scanner))
			return (create_token(HERE_DOC, scanner));
		else
			return (create_token(REDIR_IN, scanner));
	}
	if (c == '>')
	{
		if (match('>', scanner))
			return (create_token(APPEND, scanner));
		else
			return (create_token(REDIR_OUT, scanner));
	}
	if (c == '"')
		return (scan_str(scanner));
	if (is_digit(c))
		return (scan_numb(scanner));
	return (scan_identi(scanner));
}

t_token	scan_numb(t_scanner *scanner)
{
	while (is_digit(peek(scanner)))
		advance(scanner);
	return (create_token(NUMB, scanner));
}

t_token	scan_str(t_scanner *scanner)
{
	while (peek(scanner) != '"' && !is_at_end(scanner))
		advance(scanner);
	if (is_at_end(scanner))
		return (error_token("Unterminated string."));
	advance(scanner);
	return (create_token(STRING, scanner));
}

t_token	scan_identi(t_scanner *scanner)
{
	while (is_identi(peek(scanner)))
		advance(scanner);
	return (create_token(IDENTI, scanner));
}
