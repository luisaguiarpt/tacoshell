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
	while (node)
	{
		tmp_node = node->next;
		free_token_list(node);
		node = tmp_node;
	}
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

void	free_token_list(t_token_list *node)
{
	if (!node)
		return ;
	if (node->token && node->token->word)
	{
		free(node->token->word);
		node->token->word = NULL;
	}
	if (node->token && node->token->mask)
	{
		free(node->token->mask);
		node->token->mask = NULL;
	}
	if (node->token)
	{
		free(node->token);
		node->token = NULL;
	}
	free(node);
}
