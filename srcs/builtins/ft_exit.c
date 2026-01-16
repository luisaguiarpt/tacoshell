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

// May need rework, depending how we deal with the exits and frees
void	ft_exit(t_core *core)
{
	prt_n_bounce("exit", core);
	exit(EXIT_SUCCESS);
}
