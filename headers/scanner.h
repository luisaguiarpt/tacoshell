#ifndef SCANNER_H
# define SCANNER_H

# include "tacoshell.h"

// scanner.c
t_token		scan_token(t_scanner *scanner);
t_token	scan_identi(t_scanner *scanner);
t_token	scan_numb(t_scanner *scanner);
t_token	scan_str_dq(t_scanner *scanner);
t_token	scan_str_sq(t_scanner *scanner);
t_token	scan2(char c, t_scanner *scanner);
t_token	scan1(char c, t_scanner *scanner);
t_token scan_word(t_scanner *scanner, char c);

// Scanner utils - scanner_utils.c
t_scanner	*init_scanner(t_core *core);
bool	is_at_end(t_scanner *scanner);
char	peek(t_scanner *scanner);
char	advance(t_scanner *scanner);
bool	match(char expected, t_scanner *scanner);
void	skip_space(t_scanner *scanner);

#endif
