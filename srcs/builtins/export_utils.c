/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:07:00 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 22:51:59 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

static void	swap_head(t_env **sorted_head, t_env **node)
{
	t_env	*tmp;

	tmp = *sorted_head;
	*sorted_head = *node;
	(*node)->next = tmp;
}

static void	swap_body(t_env **sorted, t_env **node)
{
	t_env	*tmp;

	tmp = (*sorted)->next;
	(*sorted)->next = *node;
	(*node)->next = tmp;
}

t_env	*sort_env(t_env *unsorted)
{
	t_env	*sorted_head;
	t_env	*sorted;
	t_env	*node;

	sorted_head = NULL;
	while (unsorted)
	{
		sorted = sorted_head;
		node = unsorted;
		unsorted = unsorted->next;
		if (!sorted_head)
		{
			sorted_head = node;
			sorted_head->next = NULL;
		}
		else if (ft_strcmp(node->key, sorted_head->key) < 0)
			swap_head(&sorted_head, &node);
		else 
		{
			while (sorted->next && ft_strcmp(node->key, sorted->next->key) >= 0)
				sorted = sorted->next;
			swap_body(&sorted, &node);
		}
	}
	return (sorted_head);
}
