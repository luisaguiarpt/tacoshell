/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:23:52 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:23:53 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	skip_space(t_lexer *lexer)
{
	char	c;

	while (true)
	{
		c = peek(lexer);
		if (is_space(c))
			advance(1, lexer);
		else
			return ;
	}
}

char	advance(int i, t_lexer *lexer)
{
	lexer->current += i;
	return (*lexer->current);
}

char	peek(t_lexer *lexer)
{
	return (*lexer->current);
}

bool	match(char expected, t_lexer *lexer)
{
	if (lexer->current[1] == '\0')
		return (false);
	if (lexer->current[1] != expected)
		return (false);
	return (true);
}

bool	is_at_end(t_lexer *lexer)
{
	return (*lexer->current == 0);
}
