/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:56:08 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:56:10 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_token_operator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == TK_PIPE || type == TK_AMPERSAND || type == TK_OR
			|| type == TK_AND || type == TK_SEMI || type == TK_SEMI_SEMI)
		return (true);
	return (false);
}

bool	is_token_redir(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == TK_REDIR_OUT || type == TK_REDIR_IN
			|| type == TK_APPEND || type == TK_HERE_DOC)
		return (true);
	return (false);
}
