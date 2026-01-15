/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:56 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 16:42:41 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

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
		free(key);
		free(value);
		i++;
	}
	update_shlvl(core);
}

void	update_shlvl(t_core *core)
{
	int		shlvl_int;
	char	*shlvl_ascii;

	shlvl_int = ft_atoi(get_env(core, "SHLVL"));
	shlvl_ascii = ft_itoa(shlvl_int);
	set_env(core, "SHLVL", shlvl_ascii);
	free(shlvl_ascii);
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
