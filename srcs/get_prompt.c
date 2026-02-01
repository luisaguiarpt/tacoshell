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

/*
void	get_prompt(t_core *core)
{
	int		home_len;
	char	*cwd;
	char	*path_without_home;

	if (core->prompt)
		free(core->prompt);
	path_without_home = NULL;
	cwd = get_env(core->env, "PWD");
	home_len = ft_strlen(get_env(core->env, "HOME"));
	if (ft_strncmp(cwd, get_env(core->env, "HOME"), home_len) == 0)
		path_without_home = ft_strjoin("~", &cwd[home_len]);
	if (path_without_home)
	{
		core->prompt = ft_strjoin(path_without_home, " › ");
		free(path_without_home);
	}
	else
		core->prompt = ft_strjoin(cwd, " › ");
	//core->prompt = ft_strjoin2(TXT_BLUE, core->prompt, 1);
	//core->prompt = ft_strjoin2(core->prompt, TXT_RESET, 0);
}
*/

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
	if (home_path)
	{
		home_len = ft_strlen(home_path);
		if (ft_strncmp(cwd, home_path, home_len) == 0)
			path_without_home = ft_strjoin("~", &cwd[home_len]);
		core->prompt = ft_strjoin2(path_without_home, " > ", 0);
	}
	else
		core->prompt = ft_strjoin(cwd, " > ");
	free(cwd);
}
