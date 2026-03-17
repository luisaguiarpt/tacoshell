/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:40:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/11 16:40:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exec_node(t_shell *shell, t_ast *node)
{
	if (!node)
		return ;
	if (node->type == PIPE_NODE)
		exec_pipe(shell, node);
	else if (node->type == CMD_NODE)
		exec_cmd(shell, node);
}

int	exec_cmd(t_shell *shell, t_ast *node)
{
	if (!node)
		return (0);
	if (handle_redirs(*node->cmd->redirs, shell))
		exit_clean(shell, EXIT_FAILURE);
	if (is_builtin(node->cmd->argv[0]))
		return (builtin_handler(shell, node));
	else
		return (execve_handler(shell, node));
}

int	exec_pipe(t_shell *shell, t_ast *node)
{
	int		pipefd[2];
	pid_t	pid_in;
	pid_t	pid_out;
	int		wstatus;

	if (!node)
		return (EXIT_SUCCESS);
	disable_parent_signals();
	if (pipe(pipefd) == -1)
		exit_clean(shell, EXIT_FAILURE);
	pid_in = fork_in(shell, node->left, pipefd);
	if (pid_in < 0)
		return (EXIT_FAILURE);
	pid_out = fork_out(shell, node->right, pipefd);
	if (pid_in < 0)
		return (EXIT_FAILURE);
	close_safely(&pipefd[0]);
	close_safely(&pipefd[1]);
	waitpid(pid_in, NULL, 0);
	waitpid(pid_out, &wstatus, 0);
	if (WIFEXITED(wstatus))
		shell->exit_status = WEXITSTATUS(wstatus);
	handle_sigterm(shell, wstatus);
	setup_signals();
	return (EXIT_SUCCESS);
}

int	fork_in(t_shell *shell, t_ast *in, int pipefd[2])
{
	pid_t	pid_in;

	pid_in = fork();
	if (pid_in < 0)
	{
		close_safely(&pipefd[0]);
		close_safely(&pipefd[1]);
		exit_clean(shell, EXIT_FAILURE);
	}
	else if (pid_in == 0)
		exec_in_pipe(shell, in, pipefd);
	return (pid_in);
}

void	exec_in_pipe(t_shell *shell, t_ast *in, int pipefd[2])
{
	enable_child_signals();
	close_safely(&pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close_safely(&pipefd[1]);
	exec_node(shell, in);
	exit_clean(shell, shell->exit_status);
	return ;
}

int	fork_out(t_shell *shell, t_ast *out, int pipefd[2])
{
	pid_t	pid_out;

	pid_out = fork();
	if (pid_out < 0)
	{
		close_safely(&pipefd[0]);
		close_safely(&pipefd[1]);
		exit_clean(shell, EXIT_FAILURE);
	}
	else if (pid_out == 0)
		exec_out_pipe(shell, out, pipefd);
	return (pid_out);
}

void	exec_out_pipe(t_shell *shell, t_ast *out, int pipefd[2])
{
	enable_child_signals();
	close_safely(&pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close_safely(&pipefd[0]);
	exec_node(shell, out);
	exit_clean(shell, shell->exit_status);
	return ;
}
