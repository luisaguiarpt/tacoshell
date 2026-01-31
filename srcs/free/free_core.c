/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:38:53 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/23 15:38:54 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

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
}

void	free_core(t_core *core)
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
