#include "../incs/minishell.h"

void	lexer(t_shell *shell)
{
	t_token	*token;

	init_lexer(shell);
	init_tokens_ptr(shell);
	while (true)
	{
		shell->lexer->has_dollar = false;
		token = get_next_token(shell);
		append_token(shell, token);
		set_heredoc_delimiter(shell, token);
		expansion(shell, &token);
		if (token && token->type == TK_EOF)
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
		return (create_token_lexer(shell, TK_EOF));
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
			lexer->state = IN_SQ;
		else if (c == '\'' && lexer->state == IN_SQ)
			lexer->state = NEUTRAL;
		if (c == '"' && lexer->state == NEUTRAL)
			lexer->state = IN_DQ;
		else if (c == '"' && lexer->state == IN_DQ)
			lexer->state = NEUTRAL;
		if (c == '$' && lexer->state != IN_SQ)
			shell->lexer->has_dollar = true;
		c = advance(1, lexer);
	}
	return (create_token_lexer(shell, TK_WORD));
}

t_token	*read_op_token(t_shell *shell)
{
	char	c;

	c = peek(shell->lexer);
	if (c == '<' && match('<', shell->lexer))
		return (advance(2, shell->lexer), create_token_lexer(shell, TK_HERE_DOC));
	else if (c == '<')
		return (advance(1, shell->lexer), create_token_lexer(shell, TK_REDIR_IN));
	if (c == '>' && match('>', shell->lexer))
		return (advance(2, shell->lexer), create_token_lexer(shell, TK_APPEND));
	else if (c == '>')
		return (advance(1, shell->lexer), create_token_lexer(shell, TK_REDIR_OUT));
	if (c == '|' && match('|', shell->lexer))
		return (advance(2, shell->lexer), create_token_lexer(shell, TK_OR));
	else if (c == '|')
		return (advance(1, shell->lexer), create_token_lexer(shell, TK_PIPE));
	if (c == '&' && match('&', shell->lexer))
		return (advance(2, shell->lexer), create_token_lexer(shell, TK_AND));
	else if (c == '&')
		return (advance(1, shell->lexer), create_token_lexer(shell, TK_AMPERSAND));
	if (c == ';' && match(';', shell->lexer))
		return (advance(2, shell->lexer), create_token_lexer(shell, TK_SEMI_SEMI));
	else if (c == ';')
		return (advance(1, shell->lexer), create_token_lexer(shell, TK_SEMI));
	else
		return (advance(1, shell->lexer), create_token_lexer(shell, TK_EOF));
}

void	init_lexer(t_shell *shell)
{
	shell->lexer = ft_calloc(1, sizeof(t_lexer));
	if (!shell->lexer)
		exit_clean(shell, EXIT_FAILURE);
	shell->lexer->start = shell->line;
	shell->lexer->current = shell->line;
	shell->lexer->shell = shell;
	shell->lexer->state = NEUTRAL;
	shell->lexer->has_dollar = false;
}
