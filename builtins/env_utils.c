#include "../headers/tacoshell.h"

static void	env_append(t_core *core, t_env *new)
{
	t_env *tmp;

	tmp = core->env;
	if (core->env == NULL)
	{
		core->env = new;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	set_env(t_core *core, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;
	
	tmp = core->env;

	while(tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	env_append(core, new);
}

char	*get_env(t_core *core, char *key)
{
	t_env	*tmp;

	tmp = core->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	unset_env(t_core *core, char *key)
{
	t_env	*tmp;

	tmp = core->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
				return (EXIT_SUCCESS);
			}
		}
		tmp = tmp->next;
	}
	ft_printf("%s variable not found", key); //
	return (EXIT_FAILURE);
}

// Split modificado que so procura o primeiro '='
// para casos que usam varios '=' como por exemplo: "XMODIFIERS=@im=fcitx"
void	env_split(char *env, char **key, char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=')
		i++;
	*key = ft_substr(env, 0, i);
	while (env[j])
		j++;
	i++; //i++ ignora o '='
	*value = ft_substr(env, i, j - i); 
}
