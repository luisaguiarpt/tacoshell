#include "../headers/tacoshell.h"

t_core	init_core(void)
{
	t_core	core;
	
	core.prompt = NULL;
	core.line = NULL;
	core.scanner = NULL;
	core.tok_head = NULL;
	core.ast_root = NULL;
	core.error_code = 0;
	core.debug_counter = 0;
	core.exit_status = 0;
	return (core);
}
