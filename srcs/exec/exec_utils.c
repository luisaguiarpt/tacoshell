/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:40:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/11 16:40:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	save_original_fds(t_shell *shell)
{
	shell->orig_fds[0] = dup(STDIN_FILENO);
	shell->orig_fds[1] = dup(STDOUT_FILENO);
}

void	restore_original_fds(t_shell *shell)
{
	if (shell->orig_fds[0] != -1)
	{
		dup2(shell->orig_fds[0], STDIN_FILENO);
		close_safely(&shell->orig_fds[0]);
	}
	if (shell->orig_fds[1] != -1)
	{
		dup2(shell->orig_fds[1], STDOUT_FILENO);
		close_safely(&shell->orig_fds[1]);
	}
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
			ft_printf_fd(2, "%s: No such file or directory\n", cmd);
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
