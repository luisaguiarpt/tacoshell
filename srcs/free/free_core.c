/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:38:53 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/03 13:15:44 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

void	free_core(t_core *core)
{
	free(core->prompt);
	//free_ast(core->ast);
	free_env(core);
	core->exit_status = 0;
}
