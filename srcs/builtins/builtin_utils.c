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

#include "../../headers/tacoshell.h"

int		count_args(char **argv)
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

/*
 * echo = ft_echo
 * cd = ft_cd
 * pwd = ft_pwd
 * export = set_env
 * unset = unset_env
 * env = ft_env
 * exit = print_n_bounce
 */

int	exec_builtin(t_core *core, char **argv)
{
	char	*cmd;

	cmd = argv[0];
	if (ft_strcmp("echo", cmd) == 0)
		return (ft_echo(argv));
	else if (ft_strcmp("cd", cmd) == 0)
		return (ft_cd(core, argv));
	else if (ft_strcmp("pwd", cmd) == 0)
		return (ft_pwd(core));
	else if (ft_strcmp("export", cmd) == 0)
		return (ft_export(core, argv[1]));
	else if (ft_strcmp("unset", cmd) == 0)
		return (ft_unset(core, argv[1]));
	else if (ft_strcmp("env", cmd) == 0)
		return (ft_env(core));
	else if(ft_strcmp("exit", cmd) == 0)
		(ft_exit(core, argv));
	return (1); // just to deal with the error, int function has to return something (check in the future)
}
