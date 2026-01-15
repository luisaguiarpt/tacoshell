/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ptr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:08:23 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 20:26:56 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

static int	env_count(t_core *core)
{
	int		i;
	t_env	*current;

	i = 0;
	// if (!*core->env->key) // possibly not necessary because if there is no env vars, this function would never be called, an error would've already happened
	current = core->env;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

static char	*env_join(char *key, char *value)
{
	char	*result;

	result = ft_strjoin2(ft_strjoin(key, "="), value, 0);
	if (!result)
	{
		// MALLOC ERROR HANDLING
		return (NULL);
	}
	else
		return (result);
}

static void	free_array(char **array)
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
	free(array);
}

int	env_ptr_init(t_core *core)
{
	int		i;
	int		len;
	int		array_size;
	t_env	*current;

	i = 0;
	current = core->env;
	array_size = env_count(core);
	core->env_ptr = malloc((array_size + 1) * sizeof(char *));
	//if (!core->env_ptr)
		// MALLOC ERROR HANDLING
	while (current)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
		core->env_ptr[i] = malloc(len * sizeof(char));
		//if (!env_ptr[i])
			// MALLOC ERROR HANDLING
		core->env_ptr[i] = env_join(current->key, current->value);
		current = current->next;
		i++;
	}
	core->env_ptr[i] = NULL;
	return (EXIT_SUCCESS);
}

void	update_env_ptr(t_core *core)
{
	free_array(core->env_ptr);
	env_ptr_init(core);
}
