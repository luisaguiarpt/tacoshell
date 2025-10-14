#include "tacoshell.h"

t_scanner	init_scanner(const char *line)
{
	t_scanner	scanner;

	scanner.start = line;
	scanner.current = line;
}

t_token	scan_token(t_scanner scanner)
{
	char	c;

	scanner.start = scanner.current;
	if (*scanner.current == '\0')
		return (EOF_TOKEN);
	c = advance(scanner);
	if (c == '|')
		return (create_token(PIPE));
	if (c == ''')
		return (create_token(SINGLE_QUOTE));
	if (c == '|')
		return (create_token(DOUBLE_QUOTE));
	if (c == '(')
		return (create_token(LEFT_PAREN));
	if (c == ')')
		return (create_token(RIGHT_PAREN));
	if (c == '$')
		return (create_token(DOLLAR));
	if (c == '-')
		return (create_token(DASH));
	if (c == '<')
		if 
}

char	advance(t_scanner scanner)
{
	scanner.current++;
	return (scanner.current[-1]);
}

char	match(t_scanner scanner)
{
	if (
}
