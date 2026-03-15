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
