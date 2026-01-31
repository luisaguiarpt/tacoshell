/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:26 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 16:07:17 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

int ft_pwd(t_core *core)
{
	ft_printf(get_env(core->env, "PWD"));
	ft_printf("\n");
	return (EXIT_SUCCESS);
}
