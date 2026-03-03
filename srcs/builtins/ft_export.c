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

#include "../../headers/tacoshell.h"

static int	check_var_char(char c)
{
	if (is_digit(c))
		return (0);
	else if(is_alpha(c))
		return (0);
	else if (c == '_')
		return (0);
	else
		return (1);
}

static int	check_export_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j])
	{
		if (is_digit(argv[j][0]) || argv[j][0] == '=') // first char of a VAR can not be a digit or just an = char
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv[j]);
			return (1);
		}
		while (argv[j][i] != '=')
		{
			if (argv[j][i] == 0)
				return (0);
			if (check_var_char(argv[j][i]))
			{
				ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv[j]);
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

static int	print_export(t_core *core)
{
	t_env	*tmp_env;
	t_env	*current;

	tmp_env = populate_env(core->env_ptr);
	tmp_env = sort_env(tmp_env);
	current = tmp_env;
	while (current)
	{
		if (current->value != NULL && *current->value)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
	free_env_struct(tmp_env);
	return (EXIT_SUCCESS);
}

int	ft_export(t_core *core, char **argv)
{
	char	*key;
	char	*value;
	int		i;

	if (!argv[1])
	{
		print_export(core);
		return (EXIT_SUCCESS);
	}
	if (check_export_args(argv) == 1)
		return (EXIT_FAILURE);
	i = 1;
	while (argv[i])
	{
		env_split(argv[i], &key, &value);
		set_env(&core->env, key, value);
		update_env_ptr(core);
		free(key);
		free(value);
		i++;
	}
	return(EXIT_SUCCESS);
}
