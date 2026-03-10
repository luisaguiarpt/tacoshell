#include "../../incs/minishell.h"

void	clean(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->lexer)
		clean_lexer(shell);
//	if (shell->ast_root)
//		clean_ast(shell);
}
void	exit_clean(t_shell *shell, int exit_code)
{
	if (shell->prompt)
		free(shell->prompt);
	if (shell->line)
		free(shell->line);
	if (shell->vars)
		clean_shell_vars(shell);
	if (shell->lexer)
		clean_lexer(shell);
//	if (shell->ast_root)
//		clean_ast(shell);
	exit(exit_code);
}

void	clean_lexer(t_shell *shell)
{
	t_token_list	*tmp_node;
	t_token_list	*node;

	if (!shell->tokens)
		return ;
	node = *shell->tokens;
	free_tokens(shell->tokens);
	free(shell->tokens);
	shell->tokens = NULL;
	free(shell->lexer);
	shell->lexer = NULL;
}

void	clean_shell_vars(t_shell *shell)
{
	t_variable	*var;
	t_variable	*tmp;

	var = *shell->vars;
	while (var)
	{
		tmp = var->next;
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		if (var->exportstr)
			free(var->exportstr);
		free(var);
		var = tmp;
	}
	free(shell->vars);
}

void	free_tokens(t_token **node_ptr)
{
	t_token	*tmp;

	if (!node_ptr)
		return ;
	while (*node_ptr)
	{
		tmp = (*node_ptr)->next;
		free_token(node_ptr);
		node_ptr = &tmp;
	}
}

void	free_token(t_token **node_ptr)
{
	t_token	*node;

	if (!node_ptr)
		return ;
	node = *node_ptr;
	if (!node)
		return ;
	if (token->word)
	{
		free(token->word);
		token->word = NULL;
	}
	if (token->mask)
	{
		free(token->mask);
		token->mask = NULL;
	}
	free(node);
	node = NULL;
}
