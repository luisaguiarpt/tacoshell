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

int	heredoc_read(t_redir *curr, int heredoc_curr, t_shell *shell);
int	count_heredocs(t_redir *head);

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
	//if (fd == -1)
		//return (perror(path), EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_redirs(t_redir *head, t_shell *shell)
{
	int		heredoc_count;
	int		heredoc_curr;
	t_redir	*tmp;

	(void)shell;
	tmp = head;
	heredoc_count = count_heredocs(head);
	heredoc_curr = heredoc_count;
	while (tmp && g_signal == 0)
	{
		if (tmp->type == TK_REDIR_IN && handle_in(tmp->file_path))
			return (EXIT_FAILURE);
		else if (tmp->type == TK_REDIR_OUT && handle_out(tmp->file_path, tmp->next))
			return (EXIT_FAILURE);
		else if (tmp->type == TK_APPEND && handle_append(tmp->file_path, tmp->next))
			return (EXIT_FAILURE);
		else if (tmp->type == TK_HERE_DOC && handle_heredoc(tmp))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (g_signal);
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
// Returns a malloc'd char * of a single word (delimited by an ending space)
char	*isolate_word(char *line)
{
	char	*word;
	size_t	i;
	size_t	k;

	i = 0;
	if (!line)
		return (NULL);
	while ((line[i] && is_posix_var(line[i])) || (i == 0 && line[i] == '$'))
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	k = 0;
	while (k < i)
	{
		word[k] = line[k];
		k++;
	}
	word[i] = 0;
	return (word);
}
