/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:43 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 16:06:45 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tacoshell.h"

static int	handle_args(t_core *core, char **argv, char **dir_path)
{
	if(count_args(argv) > 2)
		return (0);
	if (!argv[1])
		*dir_path = get_env(core, "HOME");
	else if (ft_strcmp(argv[1], "-") == 0)
		*dir_path = get_env(core, "OLDPWD");
	else
		*dir_path = argv[1];
	return (1);
}

int ft_cd(t_core *core, char **argv)
{
	char	*dir_path;
	char	*current_path;
	char	tmp[PATH_MAX];

	if (!handle_args(core, argv, &dir_path))
	{
		write(2, "Error: too many args\n", 21);
		return (EXIT_FAILURE);
	}
	if (chdir(dir_path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (!getcwd(tmp, sizeof(tmp)))
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	current_path = ft_strdup(get_env(core, "PWD"));
	if (!current_path)
		return (EXIT_FAILURE);
	set_env(core, "PWD", tmp);
	set_env(core, "OLDPWD", current_path);
	free(current_path);
	return (EXIT_SUCCESS);
}
