#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tacoshell.h"

typedef struct	s_token t_token;

typedef struct	s_token
{
	t_token_type	type;
	char			*start;
	size_t			length;
	t_token			*next;
	t_token			*prev;
}				t_token;

typedef enum	e_token_type
{
	// single character tokens
	PIPE = 0,
 	LEFT_PAREN = 1,
	RIGHT_PAREN = 2,
	DOLLAR = 3,
	DASH = 4,
	// single or double character tokens
	REDIR_OUT = 5,
	REDIR_IN = 6,
	APPEND = 7,
	HERE_DOC = 8,
	// literals
	STRING = 9,
   	IDENTI = 10,
   	NUMB = 11,
	// for end
	EOF_TOK = 12,
	// for error
	ERROR_TOK = 13
}				t_token_type;

// tokenizer.c
t_token	create_token(t_token_type type, t_scanner *scanner);
t_token	error_token(char *msg);
void	append_token(t_token **head, t_token *new);
void	free_tokens(t_token *head);

#endif
