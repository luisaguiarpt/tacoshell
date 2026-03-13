/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:16:30 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/03 13:51:49 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	num_check(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (is_digit(arg[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_shell *shell, char **argv)
{
	int	exit_code;

	exit_code = -1;
	write(1, "exit\n", 5);
	if (!argv[1])
		exit_clean(shell, shell->exit_status);
	else if (!num_check(argv[1]))
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n", argv[1]);
		shell->exit_status = 2;
		exit_code = 2;
	}
	else if (argv[2])
	{
		write(2, "exit: too many arguments\n", 25);
		shell->exit_status = 2;
		return ;
	}
	if (exit_code < 0)
		exit_code = ft_atoi(argv[1]);
	shell->exit_status = (unsigned char)exit_code;
	exit_clean(shell, shell->exit_status);
}
