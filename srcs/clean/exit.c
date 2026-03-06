/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:10:46 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:10:48 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

static void	free_all(t_core *core);

void	exit_ts(t_core *core)
{
	if (core->error_code == EXIT_SUCCESS)
		prt_n_bounce("", core);
}

void	prt_n_bounce(char *msg, t_core *core)
{
	printf("%s\n", msg);
	free_all(core);
}

static void	free_all(t_core *core)
{
	free(core->scanner);
	core->scanner = NULL;
}

void	free_exit(t_core *core, int exit_status)
{
	core->exit_status = exit_status;
	full_free(core);
	exit(exit_status);
}
