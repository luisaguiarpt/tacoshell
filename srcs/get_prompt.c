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

	cwd = get_env(core, "PWD");
// skips home and user folders
	cwd++;
	while (*cwd != '/')
		cwd++;
	cwd++;
	while (*cwd != '/')
		cwd++;
	core->prompt = ft_strjoin(cwd, " › ");
}
