/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:23:36 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:23:38 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	upd_rd_state(t_token *token, t_state state, size_t *rd)
{
	token->state = state;
	*rd = *rd + 1;
}

void	read_write_token(t_token *token, size_t *rd, size_t *wr)
{
	token->word[*wr] = token->word[*rd];
	token->mask[*wr] = token->mask[*rd];
	*wr = *wr + 1;
	*rd = *rd + 1;
}

//void	check_squote_pairs(t_shell *shell, t_token *token)
//{
//	int		open;
//	int		close;
//	char	*word;
//	int		i;
//
//	while (word[i])
//	{
//		if (word[i] == '\'')
//	}
//}
