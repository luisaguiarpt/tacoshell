#include "../headers/tacoshell.h"

int	heredoc_read(t_redir *curr, int	heredoc_curr, t_core *core);
int	count_heredocs(t_redir *head);

int	handle_redirs(t_redir *head, t_core *core)
{
	int		fd;
	int		heredoc_count;
	int		heredoc_curr;
	t_redir	*tmp;

	tmp = head;
	heredoc_count = count_heredocs(head);
	heredoc_curr = heredoc_count;
	while (tmp && g_signal == 0)
	{
		if (tmp->type == REDIR_IN)
		{
			fd = open(tmp->file_path, O_RDONLY);
			if (fd == -1)
				return (perror(tmp->file_path), EXIT_FAILURE);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (tmp->type == REDIR_OUT)
		{
			fd = open(tmp->file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(tmp->file_path), EXIT_FAILURE);
			if (!tmp->next)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == APPEND)
		{
			fd = open(tmp->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror(tmp->file_path), EXIT_FAILURE);
			if (!tmp->next)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == HERE_DOC)
		{
			heredoc_curr--;
			heredoc_read(tmp, heredoc_curr, core);
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
		if (head->type == HERE_DOC)
			count++;
		head = head->next;
	}
	return (count);
}

void	write_expand(int fd, char *line, t_core *core)
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
			ft_putnbr_fd(core->exit_status, fd);
			i += 2;
		}
		else if (line[i + 1] && is_posix_var(line[i + 1]))
		{
			tmp_var = isolate_word(&line[i]);
			tmp_env = get_env(core->env, &tmp_var[1]);
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

int	heredoc_read(t_redir *curr, int heredoc_curr, t_core *core)
{
	char	*line;
	char	*tmp;
	int		fd;
	int		line_no;

	line = NULL;
	line_no = 1;
	fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 00664);
	if (fd == -1)
		return (perror("heredoc"), EXIT_FAILURE);
	signal(SIGINT, handler_heredoc);
	while (g_signal == 0)
	{
		ft_printf_fd(STDOUT_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(curr->file_path, line) == 0 || g_signal != 0)
			break ;
		else if (!line)
		{
			ft_printf_fd(STDERR_FILENO, "warning: here-document at line %d delimited by end-of-file (wanted `%s\')\n", line_no, curr->file_path);
			break ;
		}
		line_no++;
		tmp = ft_strjoin2(line, "\n", 0);
		//ft_putstr_fd(tmp, fd);
		write_expand(fd, tmp, core);
		free(tmp);
	}
	if (line)
		free(line);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	unlink(".heredoc_tmp");
	if (heredoc_curr == 0)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (g_signal);
}
