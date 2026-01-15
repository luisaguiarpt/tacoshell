/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 16:06:38 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

int	is_builtin(char *cmd)
{
	if (cmd == "echo" || cmd == "cd" || cmd == "pwd" || cmd == "export"
		|| cmd == "unset" || cmd == "env" || cmd == "exit")
		return (1);
	else
		return (0);
}

/*
 * echo = ft_echo
 * cd = ft_cd
 * pwd = ft_pwd
 * export = set_env
 * unset = unset_env
 * env = ft_env
 * exit = exit_ts
 */

void	exec_builtin(t_core *core, char *cmd, char **argv)
{
	if (ft_strcmp("echo", cmd) == 0)
		//ft_echo(core, argv[0]);
	else if (ft_strcmp("cd", cmd) == 0)
		ft_cd(core, argv[0]);
	else if (ft_strcmp("pwd", cmd) == 0)
		ft_pwd(core);
	else if (ft_strcmp("export", cmd) == 0)
		ft_export(core, argv[0]);
	else if (ft_strcmp("unset", cmd) == 0)
		ft_unset(core, arv[0]);
	else if (ft_strcmp("env", cmd) == 0)
		ft_env(core);
	else if (ft_strcmp("exit", cmd) == 0)
		exit_ts(core);
}
