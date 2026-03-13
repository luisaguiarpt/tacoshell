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

int	handle_redirs(t_redir *head, t_shell *shell)
{
	int		heredoc_count;
	int		heredoc_curr;
	t_redir	*tmp;

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
		else if (tmp->type == TK_HERE_DOC)
		{
			heredoc_curr--;
			heredoc_read(tmp, heredoc_curr, shell);
		}
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

void	write_expand(int fd, char *line, t_shell *shell)
{
	int		i;
	char	*tmp_var;
	char	*tmp_env;

	i = 0;
	while (line[i])
	{
		if (line[i] != '$')
			write(fd, &line[i++], 1);
		else if (line[i + 1] && line[i + 1] == '?')
		{
			ft_putnbr_fd(shell->exit_status, fd);
			i += 2;
		}
		else if (line[i + 1] && is_posix_var(line[i + 1]))
		{
			tmp_var = isolate_word(&line[i]);
			tmp_env = get_var_value(shell, &tmp_var[1]);
			ft_putstr_fd(tmp_env, fd);
			i += ft_strlen(tmp_var);
			free(tmp_var);
		}
	}
}

void	handler_heredoc(int signo)
{
	(void)signo;
	g_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	signal(SIGINT, handle_sigint);
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

bool	check_delimiter(char *line, char *delimiter)
{
	char	*trimmed;
	bool	match;

	trimmed = ft_strtrim(line, "\n");
	if (ft_strcmp(trimmed, delimiter) == 0)
		match = true;
	else
		match = false;
	free(trimmed);
	return (match);
}

void	heredoc_read_loop(t_shell *shell, int fd, char *delimiter)
{
	char	*line;
	char	*tmp;
	int		line_no;

	line = NULL;
	line_no = 1;
	while (g_signal == 0)
	{
		ft_printf_fd(STDOUT_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		if (check_delimiter(line, delimiter) || g_signal != 0)
			break ;
		else if (!line)
		{
			ft_printf_fd(STDERR_FILENO, "warning: here-document at line %d delimited by end-of-file (wanted `%s\')\n", line_no, delimiter);
			break ;
		}
		line_no++;
		tmp = ft_strjoin2(line, "\n", 0);
		write_expand(fd, tmp, shell);
		free(tmp);
	}
	if (line)
		free(line);
}

int	heredoc_read(t_redir *curr, int heredoc_curr, t_shell *shell)
{
	int		fd;

	fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 00664);
	if (fd == -1)
		return (perror("heredoc"), EXIT_FAILURE);
	signal(SIGINT, handler_heredoc);
	heredoc_read_loop(shell, fd, curr->file_path);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	if (heredoc_curr == 0)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (g_signal);
}
