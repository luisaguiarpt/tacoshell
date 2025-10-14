#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sysexits.h>
#include <unistd.h>

typedef struct	s_ast t_ast;
typedef struct	s_token t_token;

typedef enum	e_token_type
{
	// single character tokens
	PIPE, SINGLE_QUOTE, DOUBLE_QUOTE, LEFT_PAREN, RIGHT_PAREN,
	DOLLAR, DASH,

	// single or double character tokens
	GREATER, LESS,

	// literals
	STRING,

	// for end
	EOF_TOK
}				t_token_type;

typedef struct	s_ast
{
	t_token	token;
	t_ast	left_node;
	t_ast	right_node;
}				t_ast;

typedef struct	s_scanner
{
	const char	*start;
	const char	*current;
}				t_scanner;

typedef struct	s_core
{
	char		*line;
	char		**ast_root;
	t_scanner	scanner;
}				t_core;

typedef struct	s_token
{
	t_token_type	type;
	char			*start;
	size_t			length;
}				t_token;

// main.c
void	repl(void);

// Scanner - scanner.c

// Tokenizer - tokenizer.c
t_token	create_token(t_token_type type);

// Signal handler - signal_handler.c
void	handle_sigint(int	signo);
void	handle_sigquit(int signo);
void	setup_signals(void);

#endif
