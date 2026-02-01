#include "../headers/tacoshell.h"

void	exec_control(t_ast *node, t_core *core)
{
	pid_t	pid;
	int		wstatus;
	if (node->type == CMD_NODE && is_builtin(node->cmd->argv[0]))
	{
		core->exit_status = exec_builtin(core, node->cmd->argv);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_pipeline(node, 0, core);
	else
		waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		core->exit_status = WEXITSTATUS(wstatus);
}

// Need to implement checks for pipe() and fork() for correctness
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
		//	if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
		//		exit(1);
			core->exit_status = exec_builtin(core, node->cmd->argv);
			exit(core->exit_status);
		}
		else
		{
			if (handle_redirs(*node->cmd->redirs) == EXIT_FAILURE)
				exit(1);
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
			exec_pipeline(node->right, pipefd[0], core);
			if (input_fd != 0)
				close(input_fd);
			waitpid(pid, NULL, 0);
		}
	}
}
