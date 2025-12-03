#include "../headers/tacoshell.h"

void	ft_env(t_core *core)
{
	t_env	*current;

	current = core->env;
	while (current)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return ;
}
