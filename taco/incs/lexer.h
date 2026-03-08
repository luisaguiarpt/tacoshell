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
	TK_SEMI = 10,
	TK_SEMI_SEMI = 11,
	TK_EOF = 12 
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
	char			*mask_exp;
	bool			has_dollar;
	t_state			state;
}				t_token;

typedef struct	s_lexer
{
	char	*start;
	char	*current;
	t_shell	*shell;
	t_state	state;
	bool	has_dollar;
}				t_lexer;

// lexer.c - Lexer
void	init_lexer(t_shell *shell);
void	lexer(t_shell *shell);
t_token	*get_next_token(t_shell *shell);
t_token	*read_word_token(t_shell *shell);
t_token	*read_op_token(t_shell *shell);

// lexer_words.c - Functions related to words
int		replace_dollar(t_shell *shell, t_token *token, int i);
char	*parse_var_name(char *line);
char	*get_word_from_lexer(t_shell *shell);

// lexer_expansion.c - Expansion
void	expansion(t_shell *shell, t_token *token);
void	var_expansion(t_shell *shell, t_token *token);
void	word_split(t_shell *shell, t_token *token);
t_token	*split_token(t_shell *shell, t_token *token, int i);

// lexer_exp_utils.c - Expansion utils
void	upd_exp_mask(t_token *token, int i, char *str);
void	upd_tok_state(char c, t_token *token);
char	*set_expansion_mask(t_shell *shell, t_token *token);

// lexer_utils.c - Lexer utils
void	skip_space(t_lexer *lexer);
char	advance(int i, t_lexer *lexer);
char	peek(t_lexer *lexer);
bool	match(char	expected, t_lexer *lexer);
bool	is_at_end(t_lexer *lexer);

// lexer_tokens.c - Lexer token list utils
void	init_tokens_ptr(t_shell *shell);
t_token	*create_token_lexer(t_shell *shell, t_token_type type);
t_token	*new_token(t_shell *shell, char *word, t_token_type type);
void	append_token(t_shell *shell, t_token *new);
void	remove_token(t_shell *shell, t_token *token);

#endif
