/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:54 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:15:56 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	handle_in(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror(path), EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_out(char *path, t_redir *next)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(path), EXIT_FAILURE);
	if (!next)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append(char *path, t_redir *next)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(path), EXIT_FAILURE);
	if (!next)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_heredoc(t_redir *curr)
{
	int	fd;

	fd = curr->heredoc_fd;
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	handle_redirs(t_redir *head, t_shell *shell)
{
	t_redir	*r;
	//int		heredoc_count;
	//int		heredoc_curr;
	(void)shell;
	r = head;
	//heredoc_count = count_heredocs(head);
	//heredoc_curr = heredoc_count;
	while (r && g_signal == 0)
	{
		if (r->type == TK_REDIR_IN && handle_in(r->file_path))
			return (EXIT_FAILURE);
		else if (r->type == TK_REDIR_OUT && handle_out(r->file_path, r->next))
			return (EXIT_FAILURE);
		else if (r->type == TK_APPEND && handle_append(r->file_path, r->next))
			return (EXIT_FAILURE);
		else if (r->type == TK_HERE_DOC && handle_heredoc(r))
			return (EXIT_FAILURE);
		r = r->next;
	}
	return (g_signal);
}
