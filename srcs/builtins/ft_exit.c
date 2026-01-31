/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:16:30 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 23:31:49 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

static int	num_check(char *arg)
{
	int	i;

	i = 0;
	if(arg[i] == '+' || arg[i] == '-')
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

void	ft_exit(t_core *core, char **argv)
{
	int	exit_code;

	exit_code = -1;
	write(1, "exit\n", 5); // i think it always writes, even when it fails to exit
	if (!argv[1])
		exit_code = core->exit_status;
	else 
	{
		if (!num_check(argv[1]))
		{
			ft_printf_fd(2, "exit: %s: numeric argument required\n", argv[1]);
			exit_code = 2;
		}
    }
	if (argv[2])
	{
		write(2, "exit: too many arguments\n", 25);
		core->exit_status = 1;
		return ; // does not exit when there are too many args
	}
	if (exit_code < 0)
		exit_code = ft_atoi(argv[1]);
	core->exit_status = (unsigned char)exit_code; // casting to unsigned char deals with the 255 wrap and turns the number positive
	exit(exit_code);
}
