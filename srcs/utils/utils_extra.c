/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:09:32 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/09 15:09:33 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

bool	is_op_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ';')
		return (true);
	return (false);
}

void	update_shlvl(t_shell *shell)
{
	int		shlvl_int;
	char	*shlvl_ascii;

	shlvl_int = ft_atoi(get_var_value(shell, "SHLVL"));
	shlvl_ascii = ft_itoa(shlvl_int + 1);
	set_var(shell->vars, "SHLVL", shlvl_ascii);
	free(shlvl_ascii);
}

void	update_env_ptr(t_shell *shell)
{
	if (shell->env_ptr)
		free_array(shell->env_ptr);
	env_ptr_init(shell);
	return ;
}
