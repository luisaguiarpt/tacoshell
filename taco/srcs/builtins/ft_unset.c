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

#include "../../headers/tacoshell.h"

static void	remove_node(t_core *core, t_env *current, t_env *prev)
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
		core->env = current->next;
	free(current);
}

int	unset_env(t_core *core, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = core->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			remove_node(core, tmp, prev);
			return (EXIT_SUCCESS);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

int	ft_unset(t_core *core, char **argv)
{
	int	i;

	if (!argv[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		unset_env(core, argv[i]);
		i++;
	}
	update_env_ptr(core);
	return (EXIT_SUCCESS);
}
