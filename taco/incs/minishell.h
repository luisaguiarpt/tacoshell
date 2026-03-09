#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_signal;

// C libraries
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// libft
# include <libft.h>

// Typedefs
typedef struct	s_shell t_shell;
typedef struct	s_variable t_variable;
typedef struct	s_lexer t_lexer;
typedef struct	s_token t_token;
typedef struct	s_token_list t_token_list;

typedef enum	e_token_type t_token_type;
typedef enum	e_state t_state;

// Includes
# include "ast.h"
# include "builtins.h"
# include "taco.h"
# include "signals.h"
# include "variables.h"
# include "read_line.h"
# include "lexer.h"
# include "utils.h"
# include "clean.h"
# include "debug.h"

// main.c - Main functions
void	eval_loop(t_shell *shell);

typedef struct s_shell
{
	char			*line;
	t_variable		**vars;
	t_lexer			*lexer;
	t_token_list	**tokens;
//	t_ast			*ast_root;
	int				debug;
	int				exit_status;
}				t_shell;

#endif
