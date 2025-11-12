#include "../../headers/tacoshell.h"

static char	*set_cwd(void);

t_core	init_core(void)
{
	t_core	core;
	
	core.cwd = set_cwd();
	core.old_pwd = NULL;
	core.line = NULL;
	core.scanner = NULL;
	core.tok_head = NULL;
	core.error_code = 0;
	return (core);
}

static char	*set_cwd(void)
{
	char	cwd_path[PATH_MAX];

	getcwd(cwd_path, sizeof(cwd_path));
    return (ft_strdup(cwd_path));
}
