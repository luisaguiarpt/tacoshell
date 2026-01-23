#include "../headers/tacoshell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

static void	free_env_struct(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = next;
  }
}

static void	free_core(t_core *core)
{
	free(core->prompt);
	//free_ast(core->ast);
	if (core->env)
	{
	  free_env_struct(core->env);
	  core->env = NULL; // evitar double frees
	}
	free_array(core->env_ptr);
	core->exit_status = 0;
}

void	full_free(t_core *core)
{
	free_core(core);
}
