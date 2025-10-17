#include "tacoshell.h"

t_core	init_core(void)
{
	t_core	core;
	
	core.line = NULL;
	core.scanner = NULL;
	core.tok_head = wr_calloc(1, sizeof(t_token *), &core);
	core.error_code = 0;
	return (core);
}
