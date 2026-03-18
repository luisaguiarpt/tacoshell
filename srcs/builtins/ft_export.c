/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:45:38 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 19:53:51 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	print_export(t_shell *shell)
{
	t_variable	*current;

	current = *shell->vars;
	while (current)
	{
		if (current->value != NULL)
			ft_printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			ft_printf("declare -x %s\n", current->name);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static void	append_env(t_shell *shell, char *key, char *value)
{
	t_variable	*tmp;
	char		*new_value;

	tmp = *shell->vars;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->name) == 0)
		{
			if (!value)
			{
				set_var(shell, key, value);
				return ;
			}
			new_value = ft_strjoin2(tmp->value, value, 0);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	set_var(shell, key, value);
	return ;
}

static bool	check_append(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	check_valid_assignment(t_shell *shell, char **key, char **new_value)
{
	if (var_exists(shell, *key))
	{
		if (get_var_value(shell, *key) && !*new_value)
		{
			free(*key);
			return (false);
		}
	}
	return (true);
}

int	ft_export(t_shell *shell, char **argv)
{
	char	*key;
	char	*value;
	int		i;

	if (!argv[1])
		return (print_export(shell), EXIT_SUCCESS);
	i = 0;
	while (argv[++i])
	{
		if (check_export_arg(argv[i]) == 1)
			return (EXIT_FAILURE);
		env_split(argv[i], &key, &value);
		if (!check_valid_assignment(shell, &key, &value))
			break ;
		if (check_append(argv[i]))
			append_env(shell, key, value);
		else
			set_var(shell, key, value);
		update_env_ptr(shell);
		free(key);
		free(value);
	}
	return (EXIT_SUCCESS);
}
