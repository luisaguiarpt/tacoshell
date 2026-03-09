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

void	update_shlvl(t_shell	*shell)
{
	int		shlvl_int;
	char	*shlvl_ascii;

	shlvl_int = ft_atoi(get_variable(shell->env, "SHLVL"));
	shlvl_ascii = ft_itoa(shlvl_int + 1);
	set_variable(&shell->env, "SHLVL", shlvl_ascii);
	free(shlvl_ascii);
}

t_variable	*populate_env(char **envp)
{
	int		i;
	char	*name;
	char	*value;
	t_variable	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env_split(envp[i], &name, &value);
		env = set_variable(&env, name, value);
		free(name);
		free(value);
		i++;
	}
	return (env);
}

void	env_init(t_shell *shell, char **envp)
{
	shell->env = populate_env(envp);
	update_shlvl(shell);
	env_ptr_init(shell);
}

int	ft_env(t_shell *shell)
{
	t_variable	*current;

	current = shell->env;
	while (current)
	{
		if (current->value != NULL)
			ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
