/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:49 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/03 19:41:41 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	check_echo_flag(char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (!argv[0])
		return (0);
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] == 'n')
					j++;
				else
					return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = check_echo_flag(argv);
	flag = j - 1;
	while (argv[j])
	{
		while (argv[j][i])
		{
			write(1, &argv[j][i], 1);
			i++;
		}
		j++;
		i = 0;
		if (argv[j])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
