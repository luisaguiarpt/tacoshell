#ifndef lexer_H
# define lexer_H

# include "tacoshell.h"

// lexer.c
t_lexer	*init_lexer(t_core *core);
t_token		scan_token(t_lexer *lexer);
t_token		scan_word(t_lexer *lexer, char c);
t_token		scan_op(char c, t_lexer *lexer);
bool		is_at_end(t_lexer *lexer);

// lexer utils - lexer_utils.c
char	peek(t_lexer *lexer);
char	advance(t_lexer *lexer);
char	advance2(t_lexer *lexer);
bool	match(char expected, t_lexer *lexer);
void	skip_space(t_lexer *lexer);

// tokenizer.c
t_token	create_token(t_token_type type, t_lexer *lexer);
t_token	error_token(t_token_type type, t_lexer *lexer);
void	append_token(t_token **head, t_token *new);
void	link_tok(t_lexer *lexer, char *flag);

#endif
