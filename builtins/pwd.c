#include "../headers/tacoshell.h"
int ft_pwd(t_core *core)
{
	ft_printf(core->cwd);
	ft_printf("\n");
	return (EXIT_SUCCESS);
}
