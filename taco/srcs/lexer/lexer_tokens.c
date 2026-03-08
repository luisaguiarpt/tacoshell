#include "../incs/minishell.h"

void	init_tokens_ptr(t_shell *shell)
{
	shell->tokens = ft_calloc(1, sizeof(t_token *));
	if (!shell->tokens)
		exit_clean(shell, EXIT_FAILURE);
}

t_token	*create_token(t_shell *shell, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_clean(shell, EXIT_FAILURE);
	token->type = type;
	token->word = get_word_from_lexer(shell);
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

char	*get_word_from_lexer(t_shell *shell)
{
	t_lexer	*lexer;
	char	*word;
	size_t	len;

	lexer = shell->lexer;
	len = (int)(lexer->current - lexer->start);
	word = ft_substr(lexer->start, 0, len);
	if (!word)
		exit_clean(shell, EXIT_FAILURE);
	return (word);
}
