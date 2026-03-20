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

#include "../../incs/minishell.h"

void	print_var(char *var)
{
	int	i;

	i = 0;
	ft_printf("declare -x ");
	while (var[i] && var[i] != '=')
	{
		write(1, &var[i], 1);
		i++;
	}
	if (var[i] == '=' && var[i + 1])
	{
		write(1, &var[i], 1);
		write(1, "\"", 1);
		while (var[i++])
			write(1, &var[i], 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
	return ;
}

char	**dup_env_ptr(t_shell *shell)
{
	t_variable	*current;
	char		**dup;
	int			array_size;
	int			i;

	array_size = env_count(shell);
	current = *shell->vars;
	dup = malloc((array_size + 1) * sizeof(char *));
	if (!dup)
	{
		perror("malloc");
		exit_clean(shell, EXIT_FAILURE);
	}
	i = 0;
	while (current)
	{
		dup[i] = env_join(current->name, current->value);
		if (!dup)
			exit_clean(shell, EXIT_FAILURE);
		current = current->next;
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	sort_vars(char **vars)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (vars[i])
	{
		j = i + 1;
		while (vars[j])
		{
			if (ft_strcmp(vars[i], vars[j]) >= 0)
			{
				tmp = vars[j];
				vars[j] = vars[i];
				vars[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	check_var_char(char c)
{
	if (is_digit(c))
		return (0);
	else if (is_alpha(c))
		return (0);
	else if (c == '_')
		return (0);
	else
		return (1);
}

int	check_export_arg(char *argv)
{
	int	i;

	i = 0;
	if (is_digit(argv[0]) || argv[0] == '=')
	{
		ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv);
		return (1);
	}
	while (argv[i] != '=')
	{
		if (argv[i] == 0)
			return (0);
		if (argv[i] == '+' && argv[i + 1] == '=')
			return (0);
		if (check_var_char(argv[i]))
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv);
			return (1);
		}
		i++;
	}
	return (0);
}
