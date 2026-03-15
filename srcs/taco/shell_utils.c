/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:56:59 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:57:00 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	save_terminal_state(t_shell *shell)
{
	shell->orig_termios = ft_calloc(1, sizeof(struct termios));
	if (!shell->orig_termios)
		exit_clean(shell, EXIT_FAILURE);
	tcgetattr(STDIN_FILENO, shell->orig_termios);
}

void	restore_terminal_state(t_shell *shell)
{
	if (shell->orig_termios)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, shell->orig_termios);
}
