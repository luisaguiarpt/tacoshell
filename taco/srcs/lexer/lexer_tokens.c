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
	token->mask_exp = set_expansion_mask(shell, token);
	token->has_dollar = shell->lexer->has_dollar;
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
	token->mask_exp = set_expansion_mask(shell, token);
	token->has_dollar = shell->lexer->has_dollar;
	return (token);
}

void	append_token(t_shell *shell, t_token *new)
{
	t_token_list	*token_list_node;
	t_token_list	*tmp_list_node;

	token_list_node = ft_calloc(1, sizeof(t_token_list));
	if (!token_list_node)
		exit_clean(shell, EXIT_FAILURE);
	token_list_node->next = NULL;
	token_list_node->token = new;
	if (!*shell->tokens)
	{
		*shell->tokens = token_list_node;
		return ;
	}
	tmp_list_node = *shell->tokens;
	while (tmp_list_node->next)
		tmp_list_node = tmp_list_node->next;
	tmp_list_node->next = token_list_node;
}

void	remove_token(t_shell *shell, t_token *token)
{
	t_token_list	*node;
	t_token_list	*prev;

	node = *shell->tokens;
	if (node->token == token)
	{
		*shell->tokens = node->next;
		free_token_list(node);
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
