#include "../headers/tacoshell.h"

void	env_init(t_core *core, char **envp)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	core->env = NULL;
	while (envp[i])
	{
		env_split(envp[i], &key, &value);
		set_env(core, key, value);
		free(key); //
		free(value); //
		i++;
	}
}

int	ft_env(t_core *core)
{
	t_env	*current;

	current = core->env;
	while (current)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
