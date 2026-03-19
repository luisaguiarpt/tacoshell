/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:23:44 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:23:45 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*new_token_lexer(t_shell *shell, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_clean(shell, EXIT_FAILURE);
	token->type = type;
	token->state = NEUTRAL;
	token->word = get_word_from_lexer(shell);
	token->mask = set_expansion_mask(shell, token);
	token->has_dollar = shell->lexer->has_dollar;
	token->heredoc_delimiter = NULL;
	token->next = NULL;
	return (token);
}

t_token	*new_token(t_shell *shell, char *word, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_clean(shell, EXIT_FAILURE);
	token->type = type;
	token->state = NEUTRAL;
	token->word = word;
	token->mask = set_expansion_mask(shell, token);
	token->has_dollar = shell->lexer->has_dollar;
	token->heredoc_delimiter = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*last_token(t_shell *shell)
{
	t_token	*last;

	last = *shell->tokens;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void	append_token(t_shell *shell, t_token *new)
{
	t_token	*last;

	last = last_token(shell);
	if (!last)
	{
		*shell->tokens = new;
		return ;
	}
	last->next = new;
	new->prev = last;
}

void	remove_token(t_shell *shell, t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (!token)
		return ;
	prev = token->prev;
	next = token->next;
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev && next)
	{
		*shell->tokens = next;
		next->prev = NULL;
	}
	else if (prev && !next)
		prev->next = NULL;
	else
		*shell->tokens = NULL;
	free_token(token);
}
