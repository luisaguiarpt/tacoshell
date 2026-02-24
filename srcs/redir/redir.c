#include "../headers/tacoshell.h"

int	handle_redirs(t_redir *head)
{
	int		fd;
	t_redir	*tmp;

	tmp = head;
	while (tmp)
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
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == APPEND)
		{
			fd = open(tmp->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror(tmp->file_path), EXIT_FAILURE);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->type == HERE_DOC)
		{
			fd = open(tmp->file_path, O_RDONLY);
			if (fd == -1)
				return (perror(tmp->file_path), EXIT_FAILURE);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
