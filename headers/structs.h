#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_core t_core;
typedef struct	s_env t_env;
typedef struct	s_scanner t_scanner;
typedef struct	s_token t_token;
typedef struct	s_ast t_ast;
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
	STRING_SQ = 9,
	STRING_DQ = 10,
	WORD = 11,
	NUMB = 12,
	// for end
	EOF_TOK = 13,
	// for error
	ERROR_TOK = 14
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
	char		*prompt;
	t_env		*env;
	char		**env_ptr;
	t_ast		*ast_root;
	t_scanner	*scanner;
	t_token		**tok_head;
	int			error_code;
	bool		debug_mode;
	int			exit_status;
}				t_core;

typedef struct	s_env
{
	char		*key;
	char		*value;
	t_env		*next;
}				t_env;

typedef enum	e_state
{
	NEUTRAL = 0,
	IN_SINGLE_QUOTES = 1,
	IN_DOUBLE_QUOTES = 2
}				t_state;

typedef struct	s_scanner
{
	char		*start;
	char		*current;
	t_core		*core;
	t_state		state;
}				t_scanner;

typedef	enum	e_ast_node_type
{
	PIPE_NODE = 1,
	CMD_NODE = 2,
	BUILTIN_NODE = 3 // may or may not be used!!
}				t_ast_node_type;

typedef struct	s_redir	t_redir;

typedef struct	s_redir
{
	t_token_type	type;
	char			*file_path;
	t_redir			*next;
}				t_redir;

typedef struct	s_ast_cmd
{
	char		*cmd_path;
	char		**argv;
	t_redir		**redirs;
}				t_ast_cmd;

typedef struct	s_ast
{
	t_ast_node_type	type;
	t_ast_cmd		*cmd;
	t_ast			*left;
	t_ast			*right;
}				t_ast;

#endif
