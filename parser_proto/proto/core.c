#include "tacoshell.h"

t_core	init_core(const char *line, t_scanner scanner)
{
	t_core	core;
	
	core.line = line;
	core.scanner = init_scanner(line);
}
