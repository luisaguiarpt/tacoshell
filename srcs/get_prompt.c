/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:35 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/19 16:07:36 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

void	get_prompt(t_core *core)
{
	int		home_len;
	char	*cwd;
	char	*path_without_home;

	path_without_home = NULL;
	cwd = get_env(core, "PWD");
	home_len = ft_strlen(get_env(core, "HOME"));
	if (ft_strncmp(cwd, get_env(core, "HOME"), home_len) == 0)
		path_without_home = ft_strjoin("~", &cwd[home_len]);
	if (path_without_home)
	{
		core->prompt = ft_strjoin(path_without_home, " › ");
		free(path_without_home);
	}
	else
		core->prompt = ft_strjoin(cwd, " › ");
}
