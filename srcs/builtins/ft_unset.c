/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:56:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 17:04:18 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

int	ft_unset(t_core *core, char *arg)
{
	char	*key;
	char	*value;

	env_split(arg, &key, &value);
	unset_env(core, key);
	free(key);
	free(value);
	return (EXIT_SUCCESS);
}
