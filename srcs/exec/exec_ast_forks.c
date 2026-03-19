/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:52:10 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/19 13:52:11 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	fork_in(t_shell *shell, t_ast *in, int pipefd[2])
{
	pid_t	pid_in;

	pid_in = fork();
	if (pid_in < 0)
	{
		close_safely(&pipefd[0]);
		close_safely(&pipefd[1]);
		exit_clean(shell, EXIT_FAILURE);
	}
	else if (pid_in == 0)
		exec_in_pipe(shell, in, pipefd);
	return (pid_in);
}

int	fork_out(t_shell *shell, t_ast *out, int pipefd[2])
{
	pid_t	pid_out;

	pid_out = fork();
	if (pid_out < 0)
	{
		close_safely(&pipefd[0]);
		close_safely(&pipefd[1]);
		exit_clean(shell, EXIT_FAILURE);
	}
	else if (pid_out == 0)
		exec_out_pipe(shell, out, pipefd);
	return (pid_out);
}
