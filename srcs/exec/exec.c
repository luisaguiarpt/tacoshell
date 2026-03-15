/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:40:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/11 16:40:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exec_control(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		wstatus;
	int		fds[2];

	wstatus = 0;
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
	//if (pid == 0)
	//{
	//	close(pipefd[1]);
	//	dup2(pipefd[0], STDIN_FILENO);
	//	close(pipefd[0]);
	//	exec_pipeline(node->right, STDIN_FILENO, shell);
	//}
	//else
	//{
	//	close(pipefd[0]);
	//	dup2(pipefd[1], STDOUT_FILENO);
	//	close(pipefd[1]);
	//	exec_pipeline(node->left, input_fd, shell);
	//	close(STDOUT_FILENO);
	//	waitpid(pid, NULL, 0);
	//}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_pipeline(node->left, input_fd, shell);
		close(STDOUT_FILENO);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		exec_pipeline(node->right, pipefd[0], shell);
		if (input_fd != 0)
			close(input_fd);
		close(STDOUT_FILENO);
		waitpid(pid, NULL, 0);
	}
	exit_clean(shell, g_signal);
}
