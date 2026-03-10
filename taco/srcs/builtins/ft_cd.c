/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:43 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/04 11:05:20 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	handle_args(t_shell *shell, char **argv, char **dir_path)
{
	if (count_args(argv) > 2)
		return (0);
	if (!argv[1])
		*dir_path = get_var_value(shell, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		*dir_path = ft_strdup(get_env(shell->env, "OLDPWD"));
		printf("%s\n", *dir_path);
	}
	else if (argv[1][0] == '~' && argv[1][1] == '/')
		*dir_path = ft_strjoin(get_env(shell->env, "HOME"), &argv[1][1]);
	else
		*dir_path = ft_strdup(argv[1]);
	return (1);
}

static int	cd_checks(char *dir_path, char **tmp)
{
	if (chdir(dir_path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	*tmp = getcwd(NULL, 0);
	if (!*tmp)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_shell *shell, char **argv)
{
	char	*dir_path;
	char	*current_path;
	char	*tmp;

	tmp = NULL;
	dir_path = NULL;
	if (!handle_args(shell, argv, &dir_path))
	{
		ft_printf_fd(2, "Error: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (cd_checks(dir_path, &tmp) == EXIT_FAILURE)
	{
		free(dir_path);
		return (EXIT_FAILURE);
	}
	current_path = ft_strdup(get_env(shell->env, "PWD"));
	if (!current_path)
		free_exit(shell, EXIT_FAILURE);
	set_env(&shell->env, "PWD", tmp);
	set_env(&shell->env, "OLDPWD", current_path);
	free(current_path);
	free(dir_path);
	free(tmp);
	return (EXIT_SUCCESS);
}
