/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ptr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:08:23 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/03 16:51:34 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	env_count(t_shell *shell)
{
	int		i;
	t_env	*current;

	i = 0;
	current = shell->env;
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
		perror("malloc");
		return (NULL);
	}
	else
		return (result);
}

int	env_ptr_init(t_shell *shell)
{
	int		i;
	int		array_size;
	t_env	*current;

	i = 0;
	current = shell->env;
	array_size = env_count(shell);
	shell->env_ptr = malloc((array_size + 1) * sizeof(char *));
	if (!shell->env_ptr)
	{
		perror("malloc");
		free_exit(shell, EXIT_FAILURE);
	}
	while (current)
	{
		shell->env_ptr[i] = env_join(current->key, current->value);
		if (!shell->env_ptr)
			free_exit(shell, EXIT_FAILURE);
		current = current->next;
		i++;
	}
	shell->env_ptr[i] = NULL;
	return (EXIT_SUCCESS);
}

void	update_env_ptr(t_shell *shell)
{
	free_array(shell->env_ptr);
	env_ptr_init(shell);
}
