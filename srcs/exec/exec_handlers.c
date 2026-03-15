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

int	execve_handler(t_ast *node, t_shell *shell)
{
	int	cmd_check;
	int	exit_status;

	cmd_check = check_cmd(node);
	if (cmd_check)
	{
		exit_clean(shell, cmd_check);
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
