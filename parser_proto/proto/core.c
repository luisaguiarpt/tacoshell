#include "tacoshell.h"

t_core	init_core(void)
{
	t_core	core;
	
  core.cwd = NULL;
	core.line = NULL;
	core.scanner = NULL;
	core.tok_head = NULL;
	core.error_code = 0;
	return (core);
}
