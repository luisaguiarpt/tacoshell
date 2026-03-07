/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:11:46 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:12:13 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

t_shell	init_shell(void)
{
	t_shell	shell;

	shell.prompt = NULL;
	shell.line = NULL;
	shell.scanner = NULL;
	shell.tok_head = NULL;
	shell.ast_root = NULL;
	shell.debug_counter = 0;
	shell.exit_status = 0;
	shell.syntax_error = false;
	return (shell);
}
