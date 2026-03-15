/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:56:08 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:56:10 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	set_syntax_error(t_shell *shell)
{
	ft_printf_fd(2, "Syntax error.\n");
	shell->syntax_error = 2;
	shell->exit_status = true;
}

void	check_syntax(t_shell *shell)
{
	syntax_pipe_start(shell);

	(void)shell;
}

void	syntax_pipe_start(t_shell *shell)
{
	t_token	*head;

	head = *shell->tokens;
	if (head->type == TK_PIPE)
	{
		ft_printf_fd(STDERR_FILENO, ERRMSG_PIPE);
		shell->exit_status = 2;
		shell->syntax_error = true;
		return ;
	}
}
