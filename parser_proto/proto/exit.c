#include "tacoshell.h"

static void	free_all(t_core *core);
static void	prt_n_bounce(char *msg, t_core *core);

void	exit_ts(t_core *core)
{
	if (core->error_code == EXIT_SUCCESS)
		prt_n_bounce("", core);
}

static void	prt_n_bounce(char *msg, t_core *core)
{
	printf("%s\n", msg);
	free_all(core);
}

static void	free_all(t_core *core)
{
	free(core->scanner);
  core->scanner = NULL;
  free(core->cwd);
  core->cwd = NULL;
	//free(core);
}
