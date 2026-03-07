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

// Includes
# include "debug.h"
# include "shell.h"
# include "variables.h"
# include "clean.h"

typedef struct s_shell
{
	char			*line;
	t_variable		**vars;
//	t_lexer			*lexer;
//	t_token_list	**token_head;
//	t_ast			*ast_root;
	bool			debug;
	int				exit_status;
}				t_shell;

#endif
