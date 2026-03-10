#include "../incs/minishell.h"

void	init_tokens_ptr(t_shell *shell)
{
	shell->tokens = ft_calloc(1, sizeof(t_token *));
	if (!shell->tokens)
		exit_clean(shell, EXIT_FAILURE);
}

t_token	*create_token_lexer(t_shell *shell, t_token_type type)
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
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*last_token(t_shell *shell)
{
	t_token	*last;

	last = *shell->tokens;
	while (last)
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
	t_token	**node;
	t_token	*prev;

	node = shell->tokens;
	if (node->token == token)
	{
		*shell->tokens = NULL;
		free_token_list(node);
		node = NULL;
		return ;
	}
	prev = node;
	node = node->next;
	while (node)
	{
		if (node->token == token)
		{
			prev->next = node->next;
			free_token_list(node);
			node = NULL;
		}
		node = node->next;
	}
}
//
//t_token_list	*get_token_node(t_shell *shell, t_token *token)
//{
//	t_token_list	*node;
//
//	node = *shell->tokens;
//	while (node)
//	{
//		if (node->token == token)
//			return (node);
//		node = node->next;
//	}
//}
