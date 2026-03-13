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
# include "typedefs.h"
# include "syntax.h"
# include "ast.h"
# include "builtins.h"
# include "shell.h"
# include "signals.h"
# include "variables.h"
# include "exec.h"
# include "read.h"
# include "lexer.h"
# include "utils.h"
# include "redir.h"
# include "clean.h"
# include "debug.h"

// libft
# include <libft.h>

extern int	g_signal;

// main.c - Main functions
void	eval_loop(t_shell *shell);
void	parser(t_shell *shell);
void	executor(t_shell *shell);

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
	t_ast					*ast_root;
	char					**env_ptr;
}		t_shell;

#endif
