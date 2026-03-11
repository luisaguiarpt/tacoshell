/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:56 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 23:01:15 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
t_variable	*populate_env(char **envp)
{
	int			i;
	char		*key;
	char		*value;
	t_variable	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env_split(envp[i], &key, &value);
		env = set_var(&env, key, value);
		free(key);
		free(value);
		i++;
	}
	return (env);
}

void	env_init(t_shell *shell, char **envp)
{
	shell->vars = populate_env(envp);
	update_shlvl(shell);
	env_ptr_init(shell);
}

OBSOLETE FUNCTIONS - DELETE LATER

*/

int	ft_env(t_shell *shell)
{
	t_variable	*current;

	current = *shell->vars;
	while (current)
	{
		if (current->value != NULL)
			ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
