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
	char	*cwd;
	char	*path_without_home;
	char	*home_path;
	int		home_len;
   
	if (core->prompt)
		free(core->prompt);
	cwd	= getcwd(NULL, 0);
	home_path = get_env(core->env, "HOME");
	if (home_path && *home_path)
	{
		home_len = ft_strlen(home_path);
		if (ft_strncmp(cwd, home_path, home_len) == 0)
		{
			path_without_home = ft_strjoin("~", &cwd[home_len]);
			core->prompt = ft_strjoin2(path_without_home, " > ", 0);
		}
	}
	else
		core->prompt = ft_strjoin2(cwd, " > ", 0);
}
