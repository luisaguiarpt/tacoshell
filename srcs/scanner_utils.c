#include "../headers/tacoshell.h"

t_scanner	*init_scanner(t_core *core)
{
	t_scanner	*scanner;

	scanner = wr_calloc(1, sizeof(t_scanner), core);
	scanner->start = core->line;
	scanner->current = core->line;
	scanner->core = core;
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
