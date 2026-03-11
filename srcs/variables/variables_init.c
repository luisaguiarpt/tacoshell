/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:10:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/09 15:10:18 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_shell_vars_ptr(t_shell *shell)
{
	shell->vars = ft_calloc(1, sizeof(t_variable *));
	if (!shell->vars)
		exit_clean(shell, EXIT_FAILURE);
}

t_variable	**init_shell_vars(t_shell *shell, char **ep)
{
	t_variable	*var;
	t_variable	**vars_ptr;
	int			i;

	vars_ptr = ft_calloc(1, sizeof(t_variable *));
	if (!vars_ptr)
		exit_clean(shell, EXIT_FAILURE);
	i = 0;
	while (ep[i])
	{
		var = init_var(shell, ep[i]);
		append_shell_var(vars_ptr, var);
		i++;
	}
	if (shell->debug)
		print_env_var(vars_ptr);
	return (vars_ptr);
}

t_variable	*init_var(t_shell *shell, char *ep_var)
{
	t_variable	*var;

	var = ft_calloc(1, sizeof(t_variable));
	if (!var)
		exit_clean(shell, EXIT_FAILURE);
	var->name = init_shell_var_name(ep_var);
	if (!var->name)
		exit_clean(shell, EXIT_FAILURE);
	var->value = init_shell_var_value(ep_var);
	if (!var->value)
		exit_clean(shell, EXIT_FAILURE);
	var->exportstr= ft_strdup(ep_var);
	if (!var->exportstr)
		exit_clean(shell, EXIT_FAILURE);
	return (var);
}

t_variable	*init_var_null(t_shell *shell)
{
	t_variable	*var;

	var = ft_calloc(1, sizeof(t_variable));
	if (!var)
		exit_clean(shell, EXIT_FAILURE);
	var->name = NULL;
	var->value = NULL;
	var->exportstr = NULL;
	var->next = NULL;
	return (var);
}

char	*init_shell_var_name(char *ep_var)
{
	char	*name;
	size_t	i;

	i = 0;
	while (ep_var[i] && ep_var[i] != '+' && ep_var[i] != '=')
		i++;
	name = ft_substr(ep_var, 0, i);
	if (!name)
		return (NULL);
	return (name);
}

char	*init_shell_var_value(char *ep_var)
{
	char	*value;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (ep_var[start] && !(ep_var[start] == '+' || ep_var[start] == '='))
		start++;
	while (ep_var[start] == '+' || ep_var[start] == '=')
		start++;
	while (ep_var[end])
		end++;
	value = ft_substr(ep_var, start, end);
	if (!value)
		return (NULL);
	return (value);
}
