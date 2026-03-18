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

static void	update_cd_vars(t_shell *shell, char *oldpwd)
{
	char	*newpwd;

	set_var(shell, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		perror("getcwd");
	else
	{
		set_var(shell, "PWD", newpwd);
		free(newpwd);
	}
	update_env_ptr(shell);
	return ;
}

static int	get_new_path(t_shell *shell, char **argv, char **dir_path)
{
	if (count_args(argv) > 2)
		return (0);
	if (!argv[1])
		*dir_path = ft_strdup(get_var_value(shell, "HOME"));
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		*dir_path = ft_strdup(get_var_value(shell, "OLDPWD"));
		printf("%s\n", *dir_path);
	}
	else if (argv[1][0] == '~' && argv[1][1] == '/')
		*dir_path = ft_strjoin(get_var_value(shell, "HOME"), &argv[1][1]);
	else
		*dir_path = ft_strdup(argv[1]);
	return (1);
}

static int	change_dir(char *dir_path)
{
	if (chdir(dir_path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_shell *shell, char **argv)
{
	char	*new_path;
	char	*current_path;

	new_path = NULL;
	if (!get_new_path(shell, argv, &new_path))
	{
		ft_printf_fd(2, "Error: too many arguments\n");
		return (1);
	}
	if (change_dir(new_path) == EXIT_FAILURE)
	{
		free(new_path);
		return (EXIT_FAILURE);
	}
	current_path = ft_strdup(get_var_value(shell, "PWD"));
	if (!current_path)
		exit_clean(shell, EXIT_FAILURE);
	update_cd_vars(shell, current_path);
	free(current_path);
	free(new_path);
	return (EXIT_SUCCESS);
}
