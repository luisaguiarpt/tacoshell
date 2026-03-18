/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:07:00 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 22:51:59 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_variable	*set_var(t_shell *shell, char *name, char *value)
{
	t_variable	*var;

	var = *shell->vars;
	var = var_find(shell, name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
		return (var);
	}
	var = init_var_null(shell);
	var->name = ft_strdup(name);
	if (value)
		var->value = ft_strdup(value);
	append_shell_var(shell->vars, var);
	return (var);
}

bool	var_exists(t_shell *shell, char *var)
{
	t_variable	*tmp;

	if (!var)
		return (false);
	tmp = *shell->vars;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->name) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	env_split(char *env, char **key, char **value)
{
	int	i;
	int	j;
	int	has_plus;

	i = 0;
	j = 0;
	has_plus = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	if (env[i] == '+')
		has_plus = 1;
	*key = ft_substr(env, 0, i);
	i += has_plus;
	if (env[i] == '=')
	{
		while (env[j])
			j++;
		i ++;
		*value = ft_substr(env, i, j - i);
	}
	else
		*value = NULL;
}
