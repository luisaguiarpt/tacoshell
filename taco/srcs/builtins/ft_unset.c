/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:56:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 21:59:12 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_unset(t_shell *shell, char **argv)
{
	int	i;

	if (!argv[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (argv[i])
	{
		unset_env(shell, argv[i]);
		i++;
	}
	update_env_ptr(shell);
	return (EXIT_SUCCESS);
}
