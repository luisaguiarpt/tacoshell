#include "../incs/minishell.h"

void	save_fds(int fds[2]);
void	restore_fds(int fds[2]);
int		check_cmd(t_ast *node);
void	builtin_handler(t_ast *node, int	fds[2], t_shell *shell);

void	exec_control(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		wstatus = 0;
	int		fds[2];

	save_fds(fds);
	if (node->type == CMD_NODE && is_builtin(node->cmd->argv[0]))
		return (builtin_handler(node, fds, shell));
	pid = fork();
	if (pid == -1)
		exit_clean(shell, EXIT_FAILURE);
	if (pid == 0)
		exec_pipeline(node, STDIN_FILENO, shell);
	else
	{
		disable_parent_signals();
		waitpid(pid, &wstatus, 0);
	}
	if (WIFEXITED(wstatus))
		shell->exit_status = WEXITSTATUS(wstatus);
	restore_parent_signals();
}

void	builtin_handler(t_ast *node, int fds[2], t_shell *shell)
{
	if (handle_redirs(*node->cmd->redirs, shell) == EXIT_FAILURE)
	{
		restore_fds(fds);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	shell->exit_status = exec_builtin(shell, node->cmd->argv);
	restore_fds(fds);
	return ;
}

void	save_fds(int fds[2])
{
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
}

void	restore_fds(int fds[2])
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
}

int	execve_handler(t_ast *node, t_shell *shell)
{
	int	cmd_check;
	int	exit_status;

	cmd_check = check_cmd(node);
	if (cmd_check)
	{
		exit_clean(shell, EXIT_FAILURE);
		return (cmd_check);
	}
	if (node->cmd->cmd_path)
		execve(node->cmd->cmd_path, node->cmd->argv, shell->env_ptr);
	else if (ft_strchr(*node->cmd->argv, '/'))
		execve(node->cmd->argv[0], node->cmd->argv, shell->env_ptr);
	if (errno == EACCES || errno == ENOEXEC)
	{
		exit_status = 126;
		ft_printf_fd(2, "%s: Permission denied\n", node->cmd->argv[0]);
	}
	else
	{
		ft_printf_fd(2, "%s: command not found\n", node->cmd->argv[0]);
		exit_status = 127;
	}
	exit_clean(shell, exit_status);
	return (exit_status);
}

bool	contains_slash(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (true);
	return (false);
}

int	check_cmd(t_ast *node)
{
	char		*cmd;
	struct stat	st;

	cmd = node->cmd->argv[0];
	if (!cmd || !cmd[0])
		return (127);
	if (contains_slash(cmd))
	{
		if (stat(cmd, &st) == -1)
		{
			ft_printf_fd(2, "%s: No such file or directory\n", node->cmd->cmd_path);
			if (errno == EACCES)
				return (126);
			return (127);
		}
		if (S_ISDIR(st.st_mode))
		{
			ft_printf_fd(2, "%s: Is a directory\n", cmd);
			return (126);
		}
		return (0);
	}
	return (0);
}

// Need to implement checks for pipe() and fork() for correctness
void	exec_pipeline(t_ast *node, int input_fd, t_shell *shell)
{
	if (node->type == CMD_NODE)
		exec_cmd(node, input_fd, shell);
	else if (node->type == PIPE_NODE)
		exec_pipe(node, input_fd, shell);
}

void	exec_cmd(t_ast *node, int input_fd, t_shell *shell)
{
	if (input_fd != 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (is_builtin(node->cmd->argv[0]))
	{
		if (handle_redirs(*node->cmd->redirs, shell) == EXIT_FAILURE)
			exit(1);
		g_signal = exec_builtin(shell, node->cmd->argv);
		exit_clean(shell, g_signal);
	}
	else
	{
		if (handle_redirs(*node->cmd->redirs, shell) != EXIT_SUCCESS)
			exit_clean(shell, EXIT_FAILURE);
		exit(execve_handler(node, shell));
	}
}

void	exec_pipe(t_ast *node, int input_fd, t_shell *shell)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit_clean(shell, shell->exit_status);
	pid = fork();
	if (pid == -1)
		exit_clean(shell, shell->exit_status);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_pipeline(node->left, input_fd, shell);
	}
	else
	{
		close(pipefd[1]);
		exec_pipeline(node->right, pipefd[0], shell);
		if (input_fd != 0)
			close(input_fd);
		waitpid(pid, NULL, 0);
	}
	exit_clean(shell, g_signal);
}
