#include "../headers/tacoshell.h"

void	exec_control(t_ast *node, t_core *core)
{
	if (node->type == CMD_NODE && is_builtin(node->cmd->argv[0]))
	{
		exec_builtin(core, node->cmd->argv);
		return ;
	}
	exec_node(node, core, false);
}

void	exec_node(t_ast *node, t_core *core, bool is_child)
{
	if (!node)
		return ;
	if (node->type == PIPE_NODE)
		exec_pipe(node, core, is_child);
	else if (node->type == CMD_NODE)
		exec_cmd(node, core, is_child);
}

void	exec_pipe(t_ast *node, t_core *core, bool is_child)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipefd) == -1)
		printf("Pipe error");

	pid_left = fork();
	if (pid_left == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_node(node->left, core, true);
		exit(EXIT_SUCCESS);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exec_node(node->right, core, true);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &core->exit_status, 0);
	if (is_child)
		exit(core->exit_status);
}

void	exec_cmd(t_ast *node, t_core *core, bool is_child)
{
	pid_t	pid;

	if (is_child)
	{
		if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
			exit(1);
		if (is_builtin(node->cmd->argv[0]))
		{
			exec_builtin(core, node->cmd->argv);
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


