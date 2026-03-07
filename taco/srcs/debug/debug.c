#include "../../incs/minishell.h"

void	set_shell_debug(t_shell *shell, char **av)
{
	if (ft_strcmp(av[1], "debug") == 0)
		shell->debug = true;
}

void	print_env_var(t_shell *shell)
{
	t_variable	*var;

	var = *shell->vars;
	while (var)
	{
		printf("---\n");
		printf("name: %s\n", var->name);
		printf("value: %s\n", var->value);
		printf("export: %s\n", var->exportstr);
		var = var->next;
	}
}
