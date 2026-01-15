#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tacoshell.h"

// tokenizer.c
t_token	create_token(t_token_type type, t_scanner *scanner);
t_token	error_token(char *msg);
void	append_token(t_token **head, t_token *new);
void	free_tokens(t_token *head);

#endif
