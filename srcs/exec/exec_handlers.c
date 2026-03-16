/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:40:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/11 16:40:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	builtin_handler(t_shell *shell, t_ast *node)
{
	shell->exit_status = exec_builtin(shell, node->cmd->argv);
	return (shell->exit_status);
}

int	execve_handler(t_shell *shell, t_ast *node)
{
	pid_t	pid;
	int		wstatus;

	disable_parent_signals();
	pid = fork();
	if (pid == 0)
		return (exec_external(shell, node));
	else if (pid < 0)
		exit_clean(shell, EXIT_FAILURE);
	waitpid(pid, &wstatus, 0);
	restore_parent_signals();
	if (WIFEXITED(wstatus))
		shell->exit_status = WEXITSTATUS(wstatus);
	return (shell->exit_status);
}

int	exec_external(t_shell *shell, t_ast *node)
{
	int	cmd_check;
	int	exit_status;

	cmd_check = check_cmd(node);
	if (cmd_check)
		return (exit_clean(shell, cmd_check), cmd_check);
	if (node->cmd->cmd_path)
		execve(node->cmd->cmd_path, node->cmd->argv, shell->env_ptr);
	else if (contains_slash(*node->cmd->argv))
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

void	close_safely(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}
