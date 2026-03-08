#include "../incs/minishell.h"

void	init_lexer(t_shell *shell)
{
	shell->lexer = ft_calloc(1, sizeof(t_lexer));
	if (!shell->lexer)
		exit_clean(shell, EXIT_FAILURE);
	shell->lexer->start = shell->line;
	shell->lexer->current = shell->line;
	shell->lexer->shell = shell;
	shell->lexer->state = NEUTRAL;
}

void	lexer(t_shell *shell)
{
	t_token	*token;

	init_lexer(shell);
	init_tokens_ptr(shell);
	while (true)
	{
		token = get_next_token(shell);
		append_token(shell, token);
		if (token->type == TK_EOF)
			break ;
	}
	if (shell->debug)
		print_tokens(shell);
}

t_token	*get_next_token(t_shell *shell)
{
	skip_space(shell->lexer);
	shell->lexer->start = shell->lexer->current;
	if (is_at_end(shell->lexer))
		return (create_token(shell, TK_EOF));
	if (is_op_metachar(peek(shell->lexer)))
		return (read_op_token(shell));
	else
		return (read_word_token(shell));
}

t_token	*read_word_token(t_shell *shell)
{
	t_lexer	*lexer;
	char	c;

	lexer = shell->lexer;
	c = peek(lexer);
	while (!(is_metachar(peek(lexer)) && lexer->state == NEUTRAL) && !is_at_end(lexer))
	{
		if (c == '\'' && lexer->state == NEUTRAL)
			lexer->state = IN_SINGLE_QUOTES;
		else if (c == '\'' && lexer->state == IN_SINGLE_QUOTES)
			lexer->state = NEUTRAL;
		if (c == '"' && lexer->state == NEUTRAL)
			lexer->state = IN_DOUBLE_QUOTES;
		else if (c == '"' && lexer->state == IN_DOUBLE_QUOTES)
			lexer->state = NEUTRAL;
		c = advance(1, lexer);
	}
	return (create_token(shell, TK_WORD));
}

t_token	*read_op_token(t_shell *shell)
{
	char	c;

	c = peek(shell->lexer);
	if (c == '<')
	{
		if (match('<', shell->lexer))
			return (advance(2, shell->lexer), create_token(shell, TK_HERE_DOC));
		else
			return (advance(1, shell->lexer), create_token(shell, TK_REDIR_IN));
	}
	if (c == '>')
	{
		if (match('>', shell->lexer))
			return (advance(2, shell->lexer), create_token(shell, TK_APPEND));
		else
			return (advance(1, shell->lexer), create_token(shell, TK_REDIR_OUT));
	}
	if (c == '|' && match('|', shell->lexer))
		return (advance(2, shell->lexer), create_token(shell, TK_OR));
	if (c == '|')
		return (advance(1, shell->lexer), create_token(shell, TK_PIPE));
	if (c == '&' && match('&', shell->lexer))
		return (advance(1, shell->lexer), create_token(shell, TK_AND));
	else
		return (advance(1, shell->lexer), create_token(shell, TK_AMPERSAND));
}
