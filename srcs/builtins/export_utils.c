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
