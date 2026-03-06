/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:11:46 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:12:13 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

t_core	init_core(void)
{
	t_core	core;

	core.prompt = NULL;
	core.line = NULL;
	core.scanner = NULL;
	core.tok_head = NULL;
	core.ast_root = NULL;
	core.error_code = 0;
	core.debug_counter = 0;
	core.exit_status = 0;
	core.syntax_error = false;
	return (core);
}
