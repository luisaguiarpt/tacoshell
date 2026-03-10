/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:26 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 16:07:17 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = get_var_value(shell, "PWD");
	ft_printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
