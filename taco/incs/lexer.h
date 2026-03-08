#ifndef LEXER_H
# define LEXER_H

typedef enum	e_token_type
{
	TK_PIPE = 0,
	TK_AMPERSAND = 1,
	TK_DOLLAR = 2,
	TK_REDIR_OUT = 3,
	TK_REDIR_IN = 4,
	TK_APPEND = 5,
	TK_HERE_DOC = 6,
	TK_WORD = 7,
	TK_OR = 8,
	TK_AND = 9,
	TK_EOF = 10 
}				t_token_type;

typedef enum	e_state
{
	NEUTRAL = 0,
	IN_SINGLE_QUOTES = 1,
	IN_DOUBLE_QUOTES = 2
}				t_state;

typedef struct	s_token_list
{
	t_token			*token;
	t_token_list	*next;
}				t_token_list;

typedef struct	s_token
{
	t_token_type	type;
	char			*word;
}				t_token;

typedef struct	s_lexer
{
	char	*start;
	char	*current;
	t_shell	*shell;
	t_state	state;
}				t_lexer;

// lexer.c - Lexer
void	init_lexer(t_shell *shell);
void	lexer(t_shell *shell);
t_token	*get_next_token(t_shell *shell);
t_token	*read_word_token(t_shell *shell);
t_token	*read_op_token(t_shell *shell);

// lexer_utils.c - Lexer utils
void	skip_space(t_lexer *lexer);
char	advance(int i, t_lexer *lexer);
char	peek(t_lexer *lexer);
bool	match(char	expected, t_lexer *lexer);
bool	is_at_end(t_lexer *lexer);

// lexer_tokens.c - Lexer token list utils

void	init_tokens_ptr(t_shell *shell);
t_token	*create_token(t_shell *shell, t_token_type type);
void	append_token(t_shell *shell, t_token *new);
char	*get_word_from_lexer(t_shell *shell);

#endif
