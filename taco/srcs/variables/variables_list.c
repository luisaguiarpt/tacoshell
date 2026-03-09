/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:10:24 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/09 15:10:25 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	append_shell_var(t_variable **head, t_variable *new)
{
	t_variable	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*get_var_value(t_shell *shell, char *key)
{
	t_variable	*var;

	var = *shell->vars;
	while (var)
	{
		if (ft_strcmp(var->name, key) == 0)
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

char	*get_var_exportstr(t_shell *shell, char *key)
{
	t_variable	*var;

	var = *shell->vars;
	while (var)
	{
		if (ft_strcmp(var->name, key) == 0)
			return (var->exportstr);
		var = var->next;
	}
	return (NULL);
}
