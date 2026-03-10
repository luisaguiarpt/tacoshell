/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:19 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:20 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

// Includes
# include "ast.h"
# include "builtins.h"
# include "shell.h"
# include "signals.h"
# include "variables.h"
# include "read.h"
# include "lexer.h"
# include "utils.h"
# include "clean.h"
# include "debug.h"

// libft
# include <libft.h>

extern int	g_signal;

// Typedefs
// Structs
typedef struct s_shell		t_shell;
typedef struct s_variable	t_variable;
typedef struct s_lexer		t_lexer;
typedef struct s_token		t_token;
typedef struct s_token_list	t_token_list;

// enum
typedef enum e_token_type	t_token_type;
typedef enum e_state		t_state;

// main.c - Main functions
void	eval_loop(t_shell *shell);

typedef struct s_shell
{
	char					*line;
	char					*prompt;
	bool					syntax_error;
	int						debug;
	int						exit_status;
	t_variable				**vars;
	t_lexer					*lexer;
	t_token					**tokens;
//	t_ast					*ast_root;
}		t_shell;

#endif
