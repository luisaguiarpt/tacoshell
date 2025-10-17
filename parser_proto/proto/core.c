#include "tacoshell.h"

t_core	init_core(void)
{
	t_core	core;
	
	core.line = NULL;
	core.scanner = NULL;
	core.error_code = 0;
	return (core);
}
