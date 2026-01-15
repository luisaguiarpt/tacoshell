/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:49 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 17:02:31 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

void	handle_echo_flag(char *arg, int flag, int j)
{
	if (arg[0] == '-' && arg[1] == 'n')
	{
		flag++;
		j++;
	}
}

int ft_echo(char **argv)
{
	int	i;
	int	j;
	int flag;

	flag = 0;
	i = 0;
	j = 0;
	
	handle_echo_flag(argv[0], flag, j);
	while (argv[j])
	{
		while (argv[j][i])
		{
			write(1, &argv[j][i], 1);
			i++;
		}
		j++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

