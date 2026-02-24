#ifndef SCANNER_H
# define SCANNER_H

# include "tacoshell.h"

// scanner.c
t_scanner	*init_scanner(t_core *core);
t_token		scan_token(t_scanner *scanner);
t_token		scan_word(t_scanner *scanner, char c);
t_token		scan_op(char c, t_scanner *scanner);
bool		is_at_end(t_scanner *scanner);

// Scanner utils - scanner_utils.c
char	peek(t_scanner *scanner);
char	advance(t_scanner *scanner);
char	advance2(t_scanner *scanner);
bool	match(char expected, t_scanner *scanner);
void	skip_space(t_scanner *scanner);

// tokenizer.c
t_token	create_token(t_token_type type, t_scanner *scanner);
t_token	error_token(char *msg);
void	append_token(t_token **head, t_token *new);
void	link_tok(t_scanner *scanner, char *flag);

#endif
