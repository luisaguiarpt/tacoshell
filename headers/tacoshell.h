#ifndef TACOSHELL_H
# define TACOSHELL_H

// C libraries
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>

//libft
# include <libft.h>

// minishell headers
# include "structs.h"
# include "builtins.h"
# include "tokenizer.h"
# include "scanner.h"
# include "ast.h"

// main.c
void	repl(char **envp);

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

// Test - DELETE!!
void	exec_cmd(char *prompt, t_core *core);


#endif
