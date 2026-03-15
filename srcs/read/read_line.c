/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:54 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:15:56 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

bool	read_line(t_shell *shell)
{
	get_prompt(shell);
	shell->line = readline(shell->prompt);
	handle_ctrl_c(shell);
	if (!shell->line)
	{
		write(1, "exit\n", 5);
		exit_clean(shell, EXIT_SUCCESS);
	}
	if (!*shell->line)
		return (false);
	if (*shell->line)
		add_history(shell->line);
	return (true);
}

int	count_heredocs(t_redir *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == TK_HERE_DOC)
			count++;
		head = head->next;
	}
	return (count);
}
