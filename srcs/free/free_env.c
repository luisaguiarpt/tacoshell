/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:47:03 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/03 13:57:27 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

void	free_env_struct(t_env *env)
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
	return ;
}

void	free_env(t_core *core)
{
	if (core->env)
	{
		free_env_struct(core->env);
		core->env = NULL;
	}
	if (core->env_ptr)
	{
		free_array(core->env_ptr);
		core->env_ptr = NULL;
	}
	return ;
}
