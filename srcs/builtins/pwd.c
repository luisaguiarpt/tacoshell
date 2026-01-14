#include "../headers/tacoshell.h"
int ft_pwd(t_core *core)
{
	ft_printf(get_env(core, "PWD"));
	ft_printf("\n");
	return (EXIT_SUCCESS);
}
