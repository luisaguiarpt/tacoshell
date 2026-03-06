/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:20 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:16:21 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

char	peek(t_scanner *scanner)
{
	return (*scanner->current);
}

char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (scanner->current[0]);
}

char	advance2(t_scanner *scanner)
{
	scanner->current += 2;
	return (scanner->current[0]);
}

bool	match(char expected, t_scanner *scanner)
{
	if (scanner->current[1] == '\0')
		return (false);
	if (scanner->current[1] != expected)
		return (false);
	//scanner->current += 2;
	return (true);
}

void	skip_space(t_scanner *scanner)
{
	char	c;
	while (1)
	{
		c = peek(scanner);
		if (c == ' ' || c == '\r' || c == '\t')
			advance(scanner);
		else
			return ;
	}
}
