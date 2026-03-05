#include "../headers/tacoshell.h"

void	save_fds(int fds[2]);
void	restore_fds(int fds[2]);
int		check_cmd(t_ast *node);
void	builtin_handler(t_ast *node, int	fds[2], t_core *core);

void	exec_control(t_ast *node, t_core *core)
{
	pid_t	pid;
	int		wstatus = 0;
	int		fds[2];

	save_fds(fds);
	if (node->type == CMD_NODE && is_builtin(node->cmd->argv[0]))
		return (builtin_handler(node, fds, core));
	pid = fork();
	if (pid == -1)
		free_exit(core, EXIT_FAILURE);
	if (pid == 0)
		exec_pipeline(node, STDIN_FILENO, core);
	else
		waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		core->exit_status = WEXITSTATUS(wstatus);
}

void	builtin_handler(t_ast *node, int fds[2], t_core *core)
{
	if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
	{
		restore_fds(fds);
		core->exit_status = EXIT_FAILURE;
		return ;
	}
	core->exit_status = exec_builtin(core, node->cmd->argv);
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

int	execve_handler(t_ast *node, t_core *core)
{
	int	cmd_check;
	int	exit_status;

	cmd_check = check_cmd(node);
	if (cmd_check)
	{
		core->exit_status = cmd_check;
		full_free(core);
		return (cmd_check);
	}
	if (node->cmd->cmd_path)
		execve(node->cmd->cmd_path, node->cmd->argv, core->env_ptr);
	else
		execve(node->cmd->argv[0], node->cmd->argv, core->env_ptr);
	ft_printf_fd(2, "%s: command not found\n", node->cmd->argv[0]);
	if (errno == EACCES)
		exit_status = 126;
	else
		exit_status = 127;
	full_free(core);
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
			if (errno == ENOENT || errno == ENOTDIR)
				return (127);
			if (errno == EACCES)
				return (126);
			return (127);
		}
		if (S_ISDIR(st.st_mode))
		{
			ft_printf_fd(2, "%s: Is a directory\n", cmd);
			return (126);
		}
		if (access(cmd, X_OK) == -1)
		{
			ft_printf_fd(2, "%s: Permission denied\n", cmd);
			return (126);
		}
		return (0);
	}
	else
	{
		if (node->cmd->cmd_path && stat(node->cmd->cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
			return (127);
		return (0);
	}
}

// Need to implement checks for pipe() and fork() for correctness
void	exec_pipeline(t_ast *node, int input_fd, t_core *core)
{
	if (node->type == CMD_NODE)
		exec_cmd(node, input_fd, core);
	else if (node->type == PIPE_NODE)
		exec_pipe(node, input_fd, core);
}

void	exec_cmd(t_ast *node, int input_fd, t_core *core)
{
	if (input_fd != 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (is_builtin(node->cmd->argv[0]))
	{
		if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
			exit(1);
		core->exit_status = exec_builtin(core, node->cmd->argv);
		exit(core->exit_status);
	}
	else
	{
		if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
			exit(1);
		exit(execve_handler(node, core));
	}
}

void	exec_pipe(t_ast *node, int input_fd, t_core *core)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(core->exit_status);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_pipeline(node->left, input_fd, core);
	}
	else
	{
		close(pipefd[1]);
		exec_pipeline(node->right, pipefd[0], core);
		if (input_fd != 0)
			close(input_fd);
		waitpid(pid, NULL, 0);
	}
}
