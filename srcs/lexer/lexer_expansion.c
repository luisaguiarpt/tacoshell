/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:23:31 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:23:32 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	expansion(t_shell *shell, t_token **token)
{
	var_expansion(shell, token);
	word_split(shell, *token);
	quote_remove(shell, *token);
}

void	var_expansion(t_shell *shell, t_token **token)
{
	int		i;
	t_token	*tok;

	tok = *token;
	if (tok->has_dollar == 0)
		return ;
	i = 0;
	while (tok->word && tok->word[i])
	{
		upd_tok_state(tok->word[i], tok);
		if (tok->state == IN_SQ)
			i++;
		else if (tok->word[i] == '$')
			i += replace_dollar(shell, tok, i);
		else
			i++;
	}
	if (tok->has_dollar && !ft_strlen(tok->word))
	{
		remove_token(shell, *token);
		*token = NULL;
	}
}

void	word_split(t_shell *shell, t_token *token)
{
	t_token			*new_token;
	int				i;

	i = 0;
	if (!token)
		return ;
	token->state = NEUTRAL;
	while (token->word && token->word[i])
	{
		if (token->state == NEUTRAL && token->word[i] == '"')
			token->state = IN_DQ;
		else if (token->state == IN_DQ && token->word[i] == '"')
			token->state = NEUTRAL;
		if (token->word[i] == ' ' && token->mask[i] == '1' && token->state == NEUTRAL)
		{
			new_token = split_token(shell, token, i);
			append_token(shell, new_token);
			i = 0;
		}
		else
			i++;
	}
}

// t->state == 0 because of norminette (0 == NEUTRAL)
void	quote_remove(t_shell *shell, t_token *t)
{
	size_t	rd;
	size_t	wr;

	if (!t || !t->word || !t->mask)
		return ;
	rd = 0;
	wr = 0;
	t->state = NEUTRAL;
	while (t->word[rd])
	{
		if (t->mask[rd] == '0' && t->word[rd] == '"' && t->state == NEUTRAL)
			upd_rd_state(t, IN_DQ, &rd);
		else if (t->mask[rd] == '0' && t->word[rd] == '"' && t->state == IN_DQ)
			upd_rd_state(t, NEUTRAL, &rd);
		else if (t->mask[rd] == '0' && t->word[rd] == '\'' && t->state == 0)
			upd_rd_state(t, IN_SQ, &rd);
		else if (t->mask[rd] == '0' && t->word[rd] == '\'' && t->state == IN_SQ)
			upd_rd_state(t, NEUTRAL, &rd);
		else
			read_write_token(t, &rd, &wr);
	}
	t->word[wr] = '\0';
	t->mask[wr] = '\0';
	(void)shell;
}

t_token	*split_token(t_shell *shell, t_token *token, int i)
{
	t_token	*new_tok;
	char	*new_word;
	char	*new_mask;
	char	*tmp;

	new_word = ft_substr(token->word, i + 1, ft_strlen(token->word) - (i + 1));
	if (!new_word)
		exit_clean(shell, EXIT_FAILURE);
	new_mask = ft_substr(token->mask, i + 1, ft_strlen(token->mask) - (i + 1));
	if (!new_mask)
		exit_clean(shell, EXIT_FAILURE);
	new_tok = new_token(shell, new_word, TK_WORD);
	free(new_tok->mask);
	new_tok->mask = new_mask;
	tmp = token->word;
	token->word = ft_substr(token->word, 0, i);
	if (!token->word)
		exit_clean(shell, EXIT_FAILURE);
	free(tmp);
	tmp = token->mask;
	token->mask = ft_substr(token->mask, 0, i);
	if (!token->mask)
		exit_clean(shell, EXIT_FAILURE);
	free(tmp);
	return (new_tok);
}
