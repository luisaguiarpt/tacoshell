#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_core t_core;
typedef struct	s_ast t_ast;
typedef struct	s_env t_env;
typedef struct	s_scanner t_scanner;
typedef struct	s_token t_token;
typedef enum	e_token_type t_token_type;

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

typedef struct	s_token
{
	t_token_type	type;
	char			*start;
	size_t			length;
	t_token			*next;
	t_token			*prev;
}				t_token;

typedef struct	s_core
{
	char		*line;
	t_env		*env;
	t_ast		**ast_root;
	t_scanner	*scanner;
	t_token		**tok_head;
	int			error_code;
}				t_core;

typedef struct	s_ast
{
	t_token		token;
	t_ast		*left;
	t_ast		*right;
}				t_ast;

typedef struct	s_env
{
	char		*key;
	char		*value;
	t_env		*next;
}				t_env;

typedef struct	s_scanner
{
	char	*start;
	char	*current;
	t_core		*core;
}				t_scanner;

#endif
