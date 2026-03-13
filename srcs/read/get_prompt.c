/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:35 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/03 14:09:41 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*shorten_home_path(t_shell *shell, char *cwd)
{
	char	*path_without_home;
	char	*home_path;
	int		home_len;

	home_path = get_var_value(shell, "HOME");
	if (home_path && *home_path)
	{
		home_len = ft_strlen(home_path);
		if (ft_strncmp(cwd, home_path, home_len) == 0)
		{
			path_without_home = ft_strjoin("~", &cwd[home_len]);
			return (ft_strjoin2(path_without_home, "> ", 0));
		}
	}
	return (ft_strjoin(cwd, "> "));
}

void	get_prompt(t_shell *shell)
{
	char	*cwd;
 
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (shell->prompt)
		free(shell->prompt);
		//exit_clean(shell, EXIT_FAILURE);
	shell->prompt = shorten_home_path(shell, cwd);
	free(cwd);
}
