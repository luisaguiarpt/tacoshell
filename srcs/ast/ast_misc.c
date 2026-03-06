/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:04:36 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:04:38 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

bool	is_pipe(t_token token)
{
	if (token.type == PIPE)
		return (true);
	return (false);
}

bool	is_word(t_token token)
{
	if (token.type == WORD || token.type == DOLLAR || token.type == DASH)
		return (true);
	return (false);
}

// This function checks to see if the token is a redir token,
// and if the following token is a valid token
bool	is_redir_operator(t_token token)
{
	if (token.type >= REDIR_OUT && token.type <= HERE_DOC)
		return (true);
	return (false);
}

int	precedence(t_token token)
{
	if (token.type == PIPE)
		return (2);
	if (token.type >= REDIR_OUT && token.type <= HERE_DOC)
		return (3);
	else
		return (4);
}
