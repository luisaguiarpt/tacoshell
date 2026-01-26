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

#include "../../headers/tacoshell.h"

int	ft_unset(t_core *core, char **argv)
{
	if (!argv[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return (EXIT_FAILURE);
    }
	unset_env(core, argv[1]);
	update_env_ptr(core);
	return (EXIT_SUCCESS);
}
