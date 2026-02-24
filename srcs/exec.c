#include "../headers/tacoshell.h"

void	exec_control(t_ast *node, t_core *core)
{
	pid_t	pid;
	int		wstatus = 0;

	if (node->type == CMD_NODE && is_builtin(node->cmd->argv[0]))
	{
		if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
			return ;
		core->exit_status = exec_builtin(core, node->cmd->argv);
		return ;
	}
	pid = fork();
	// fork GUARD!
	if (pid == 0)
		exec_pipeline(node, STDIN_FILENO, core);
	else
		waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		core->exit_status = WEXITSTATUS(wstatus);
}

int	execve_handler(t_ast *node, t_core *core)
{
	struct stat	path_stat;

	if (stat(node->cmd->cmd_path, &path_stat) == -1)
	{
		perror("stat");
		return (127);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(2, "%s: Is a directory\n", node->cmd->cmd_path);
		return (126);
	}
	execve(node->cmd->cmd_path, node->cmd->argv, core->env_ptr);
	// Handle specific errors based on errno.
	if (errno == ENOENT) {
	    ft_printf_fd(2, "%s: Command not found\n", node->cmd->argv[1]);
	    return 127; // Exit code for command not found.
	} else if (errno == EACCES) {
	    ft_printf_fd(2, "%s: Permission denied\n", node->cmd->argv[1]);
	    return 126; // Exit code for permission denied.
	} else if (errno == EISDIR) {
	    ft_printf_fd(2, "%s: Is a directory\n", node->cmd->argv[1]);
	    return 126; // Exit code for trying to execute a directory.
	} else if (errno == ENOEXEC) {
	    ft_printf_fd(2, "%s: exec format error\n", node->cmd->argv[1]);
	    return 126; // Exit code for invalid executable format.
	} else {
	    // Use perror to display the error message for any other error.
	    perror("execve");
	    return 1; // General error exit code.
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

	pipe(pipefd);
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
