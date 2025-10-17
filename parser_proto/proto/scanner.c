#include "tacoshell.h"

t_token	scan_identifier(t_scanner *scanner);
t_token	scan_str(t_scanner *scanner);
t_token	scan2(char c, t_scanner *scanner);
t_token	scan1(char c, t_scanner *scanner);

t_scanner	*init_scanner(t_core *core)
{
	t_scanner	*scanner;

	scanner = wr_calloc(1, sizeof(t_scanner), core);
	scanner->start = core->line;
	scanner->current = core->line;
	return (scanner);
}

bool	is_at_end(t_scanner *scanner)
{
	return (*scanner->current == 0);
}

char	peek(t_scanner *scanner)
{
	return (*scanner->current);
}

char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (scanner->current[-1]);
}

bool	match(char expected, t_scanner *scanner)
{
	if (*scanner->current == '\0')
		return (false);
	if (*scanner->current != expected)
		return (false);
	scanner->current++;
	return (true);
}

void	skip_space(t_scanner *scanner)
{
	char	c;
	while (1)
	{
		c = peek(scanner);
		if (c == ' ' || c == '\r' || c == '\t')
			advance(scanner);
		else
			return ;
	}
}

t_token	scan_token(t_scanner *scanner)
{
	char		c;

	skip_space(scanner);
	scanner->start = scanner->current;
	if (*scanner->current == '\0')
		return (create_token(EOF_TOK, scanner));
	c = advance(scanner);
	return (scan1(c, scanner));
}

t_token	scan1(char c, t_scanner *scanner)
{
	if (c == '|')
		return (create_token(PIPE, scanner));
	if (c == '(')
		return (create_token(LEFT_PAREN, scanner));
	if (c == ')')
		return (create_token(RIGHT_PAREN, scanner));
	if (c == '$')
		return (create_token(DOLLAR, scanner));
	return (scan2(c, scanner));
}

t_token	scan2(char c, t_scanner *scanner)
{
	if (c == '<')
	{
		if (match('<', scanner))
			return (create_token(LESS_LESS, scanner));
		else
			return (create_token(LESS, scanner));
	}
	if (c == '>')
	{
		if (match('>', scanner))
			return (create_token(GREATER_GREATER, scanner));
		else
			return (create_token(GREATER, scanner));
	}
	if (c == '"')
		return (scan_str(scanner));
	return (scan_identifier(scanner));
}

t_token	scan_str(t_scanner *scanner)
{
	while (peek(scanner) != '"' && !is_at_end(scanner))
	{
		advance(scanner);
	}
	if (is_at_end(scanner))
		return (error_token("Unterminated string."));
	advance(scanner);
	return (create_token(STRING, scanner));
}

t_token	scan_identifier(t_scanner *scanner)
{
	while (is_alpha(peek(scanner)) || peek(scanner) == '-' || peek(scanner) == '.')
		advance(scanner);
	return (create_token(IDENTI, scanner));
}
