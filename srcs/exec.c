#include "../headers/tacoshell.h"

void	exec_control(t_ast *node, t_core *core)
{
	pid_t	pid;
	if (node->type == CMD_NODE && is_builtin(node->cmd->argv[0]))
	{
		core->exit_status = exec_builtin(core, node->cmd->argv);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_pipeline(node, 0, core);
	else
		waitpid(pid, NULL, 0);
	//exec_node(node, core, false);
}

/*
void	exec_node(t_ast *node, t_core *core, bool is_child)
{
	if (!node)
		return ;
	if (node->type == PIPE_NODE)
		exec_pipe(node, 0, core);
	else if (node->type == CMD_NODE)
		exec_cmd(node, core, is_child);
}
*/

void	exec_pipeline(t_ast *node, int input_fd, t_core *core)
{
	int		pipefd[2];
	pid_t	pid;

	if (node->type == CMD_NODE)
	{
		if (input_fd != 0)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (is_builtin(node->cmd->argv[0]))
		{
			core->exit_status = exec_builtin(core, node->cmd->argv);
			exit(0);
		}
		else
		{
			execve(node->cmd->cmd_path, node->cmd->argv, core->env_ptr);
			perror("execve failed");
			exit(127);
		}
	}
	else if (node->type == PIPE_NODE)
	{
		pipe(pipefd);
		pid = fork();
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
			waitpid(pid, NULL, 0);
			exec_pipeline(node->right, pipefd[0], core);
		}
	}
}

/*
void	exec_pipe(t_ast *node, t_core *core, bool is_child)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid_left;
	pid_t	pid_right;
	int		wstatus;

	prev_fd = -1;
	if (pipe(pipefd) == -1)
		printf("Pipe error");
	core->debug_counter++;
	pid_left = fork();
	if (pid_left == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_node(node->left, core, true);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exec_node(node->right, core, true);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &wstatus, 0);
	if (is_child && WIFEXITED(wstatus))
		core->exit_status = WEXITSTATUS(wstatus);
}

void	exec_cmd(t_ast *node, t_core *core, int	in_fd, int out_fd)
{
	pid_t	pid;

	if (is_child)
	{
		if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
			exit(1);
		if (is_builtin(node->cmd->argv[0]))
		{
			core->exit_status = exec_builtin(core, node->cmd->argv);
			exit(0);
		}
		else
		{
			execve(node->cmd->cmd_path, node->cmd->argv, core->env_ptr);
			perror("execve failed");
			exit(127);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
				exit(1);
			execve(node->cmd->cmd_path, node->cmd->argv, core->env_ptr);
			perror("execve failed");
			exit(127);
		}
		waitpid(pid, &core->exit_status, 0);
	}
}
*/

