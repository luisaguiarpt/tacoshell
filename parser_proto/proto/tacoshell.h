#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct	s_ast t_ast;
typedef struct	s_token t_token;
typedef struct	s_core t_core;

typedef enum	e_token_type
{
	// single character tokens
	PIPE, SINGLE_QUOTE, DOUBLE_QUOTE, LEFT_PAREN, RIGHT_PAREN,
	DOLLAR, DASH,
	// single or double character tokens
	GREATER, LESS, GREATER_GREATER, LESS_LESS,
	// literals
	STRING, IDENTI,
	// for end
	EOF_TOK,
	// for error
	ERROR_TOK
}				t_token_type;

typedef struct	s_scanner
{
	char	*start;
	char	*current;
	t_core		*core;
}				t_scanner;

typedef struct	s_core
{
	char	*line;
	t_ast		**ast_root;
	t_scanner	*scanner;
	int			error_code;
}				t_core;

typedef struct	s_token
{
	t_token_type	type;
	char			*start;
	size_t			length;
}				t_token;

typedef struct	s_ast {
	t_token	token;
	t_ast	*left_node;
	t_ast	*right_node;
}				t_ast;

// main.c
void	repl(void);

// Scanner - scanner.c
t_scanner	*init_scanner(t_core *core);
t_token		scan_token(t_scanner *scanner);

// Tokenizer - tokenizer.c
t_token	create_token(t_token_type type, t_scanner *scanner);
t_token	error_token(char *msg);

// Core - core.c
t_core	init_core(void);

// Wrapper functions - wrapper_*.c
void	*wr_calloc(size_t nmemb, size_t size, t_core *core);

// Exit handling - exit.c
void	exit_ts(t_core *core);

// Signal handler - signal_handler.c
void	handle_sigint(int	signo);
void	handle_sigquit(int signo);
void	setup_signals(void);

// Utils - utils.c
size_t	ft_strlen(char	*str);
bool	is_alpha(char c);

#endif
