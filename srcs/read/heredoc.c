/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:15:54 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:15:56 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	heredoc_read(t_redir *curr, int heredoc_curr, t_shell *shell)
{
	int		fd;

	fd = -1;
	fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 00664);
	if (fd == -1)
		return (perror("heredoc"), EXIT_FAILURE);
	signal(SIGINT, handler_heredoc);
	heredoc_read_loop(shell, fd, curr->heredoc_delimiter);
	close(fd);
	if (heredoc_curr == 0 && g_signal == 0)
		curr->heredoc_fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	setup_signals();
	return (fd);
}

void	heredoc_read_loop(t_shell *shell, int fd, char *delimiter)
{
	char	*line;
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
			ft_printf_fd(STDERR_FILENO, ERRMSG_HD_EOF, line_no, delimiter);
			break ;
		}
		line_no++;
		write_expand(fd, line, shell);
		free(line);
	}
	if (line)
		free(line);
}

void	set_heredoc_delimiter(t_shell *shell, t_token *node)
{
	(void)shell;
	if (!node->prev)
		return ;
	if (node->prev->type == TK_HERE_DOC)
		node->prev->heredoc_delimiter = ft_strdup(node->word);
}

bool	check_delimiter(char *line, char *delimiter)
{
	char	*trimmed;
	bool	match;

	if (!line)
		return (false);
	trimmed = ft_strtrim(line, "\n");
	if (ft_strcmp(trimmed, delimiter) == 0)
		match = true;
	else
		match = false;
	free(trimmed);
	return (match);
}

void	write_expand(int fd, char *line, t_shell *shell)
{
	int		i;
	char	*tmp_var;
	char	*tmp_env;

	i = 0;
	while (line && line[i])
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
