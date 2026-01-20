/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:49 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 21:49:12 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

static int	check_echo_flag(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n')
		return (1);
	else
		return (0);
}

int ft_echo(char **argv)
{
	int	i;
	int	j;
	int flag;

	i = 0;
	flag = check_echo_flag(argv[1]);
	j = (check_echo_flag(argv[0]) + 1); // + 1 to skip argv[0]

	while (argv[j])
	{
		while (argv[j][i])
		{
			write(1, &argv[j][i], 1);
			i++;
		}
		write(1, " ", 1);
		i = 0;
		j++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

