/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:00:03 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/11 15:00:04 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	update_shlvl(t_shell *shell)
{
	int		shlvl_int;
	char	*shlvl_ascii;

	shlvl_ascii = get_var_value(shell, "SHLVL");
	if (shlvl_ascii == NULL)
		shlvl_int = 0;
	else 
		shlvl_int = ft_atoi(shlvl_ascii);
	shlvl_ascii = ft_itoa(shlvl_int + 1);
	set_var(shell, "SHLVL", shlvl_ascii);
	update_env_ptr(shell);
	free(shlvl_ascii);
}

void	update_env_ptr(t_shell *shell)
{
	if (shell->env_ptr)
	{
		free_array(shell->env_ptr);
		shell->env_ptr = NULL;
	}
	env_ptr_init(shell);
	return ;
}
