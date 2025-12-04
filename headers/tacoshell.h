#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <limits.h>
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
#include <libft.h>

typedef struct	s_ast t_ast;
typedef struct	s_token t_token;
typedef struct	s_core t_core;
typedef struct	s_env t_env;

typedef enum	e_token_type
{
	// single character tokens
	PIPE, LEFT_PAREN, RIGHT_PAREN,
	DOLLAR, DASH,
	// single or double character tokens
	REDIR_OUT, REDIR_IN, APPEND, HERE_DOC,
	// literals
	STRING, IDENTI, NUMB,
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
	char		*line;
	t_env		*env;
	t_ast		**ast_root;
	t_scanner	*scanner;
	t_token		**tok_head;
	int			error_code;
}				t_core;

typedef struct	s_token
{
	t_token_type	type;
	char			*start;
	size_t			length;
	t_token			*next;
	t_token			*prev;
}				t_token;

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

// main.c
void	repl(char **envp);

// Scanner - scanner.c
t_token		scan_token(t_scanner *scanner);
t_token	scan_identi(t_scanner *scanner);
t_token	scan_numb(t_scanner *scanner);
t_token	scan_str(t_scanner *scanner);
t_token	scan2(char c, t_scanner *scanner);
t_token	scan1(char c, t_scanner *scanner);

// Scanner utils - scanner_utils.c
t_scanner	*init_scanner(t_core *core);
bool	is_at_end(t_scanner *scanner);
char	peek(t_scanner *scanner);
char	advance(t_scanner *scanner);
bool	match(char expected, t_scanner *scanner);
void	skip_space(t_scanner *scanner);

// Tokenizer - tokenizer.c
t_token	create_token(t_token_type type, t_scanner *scanner);
t_token	error_token(char *msg);
void	append_token(t_token **head, t_token *new);
void	free_tokens(t_token *head);

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
//size_t	ft_strlen(char	*str);
bool	is_alpha(char c);
bool	is_digit(char c);
bool	is_identi(char c);

// Builtins
int	ft_cd(t_core *core, char *dir_path);
int	ft_echo(int nflag, char *arg);
int	ft_pwd(t_core *core);
int	ft_env(t_core *core);

// Test - DELETE!!
void	exec_cmd(char *prompt, t_core *core);

// Env
void	env_init(t_core *core, char **envp);
void	set_env(t_core *core, char *key, char *value);
char	*get_env(t_core *core, char *key);
/*
void	unset_env(t_core *core, char *key);
*/
void	env_split(char *env, char **key, char **value);

#endif
