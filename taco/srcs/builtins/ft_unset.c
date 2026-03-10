/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:56:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 21:59:12 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	remove_node(t_shell *shell, t_env *current, t_env *prev)
{
	bool	first_node;

	first_node = 0;
	if (!prev)
		first_node = 1;
	else
		prev->next = current->next;
	free(current->key);
	free(current->value);
	if (first_node)
		shell->env = current->next;
	free(current);
}

int	unset_var(t_shell *shell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->vars;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			remove_node(shell, tmp, prev);
			return (EXIT_SUCCESS);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

int	ft_unset(t_shell *shell, char **argv)
{
	int	i;

	if (!argv[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		unset_var(shell, argv[i]);
		i++;
	}
	update_env_ptr(shell);
	return (EXIT_SUCCESS);
}
