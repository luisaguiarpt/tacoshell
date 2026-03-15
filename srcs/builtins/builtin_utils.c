/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 23:16:18 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0
		|| ft_strcmp("cd", cmd) == 0
		|| ft_strcmp("pwd", cmd) == 0
		|| ft_strcmp("export", cmd) == 0
		|| ft_strcmp("unset", cmd) == 0
		|| ft_strcmp("env", cmd) == 0
		|| ft_strcmp("exit", cmd) == 0)
		return (true);
	else
		return (false);
}

int	exec_builtin(t_shell *shell, char **argv)
{
	char	*cmd;

	cmd = argv[0];
	if (ft_strcmp("echo", cmd) == 0)
		return (ft_echo(argv));
	else if (ft_strcmp("cd", cmd) == 0)
		return (ft_cd(shell, argv));
	else if (ft_strcmp("pwd", cmd) == 0)
		return (ft_pwd(shell));
	else if (ft_strcmp("export", cmd) == 0)
		return (ft_export(shell, argv));
	else if (ft_strcmp("unset", cmd) == 0)
		return (ft_unset(shell, argv));
	else if (ft_strcmp("env", cmd) == 0)
		return (ft_env(shell));
	else if (ft_strcmp("exit", cmd) == 0)
		(ft_exit(shell, argv));
	return (shell->exit_status);
}
