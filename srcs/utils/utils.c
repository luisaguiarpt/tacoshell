/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:57:40 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:57:42 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

bool	is_posix_var(char c)
{
	if (is_digit(c) || is_alpha(c) || c == '_')
		return (true);
	return (false);
}

bool	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

bool	is_identi(char c)
{
	if (is_alpha(c) || c == '.' || c == '-' || is_digit(c) || c == '/')
		return (true);
	return (false);
}

bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

// characters that can't be part of a variable name
// with the exception of " and ',
// which for this purpose are considered and later stripped
bool	is_metachar(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&'
		|| c == ';' || c == '(' || c == ')' || c == '<' || c == '>')
		return (true);
	return (false);
}
