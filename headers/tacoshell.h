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
# include <fcntl.h>
# include <sys/wait.h>

//libft
# include <libft.h>

// minishell headers
# include "structs.h"
# include "builtins.h"
# include "tokenizer.h"
# include "scanner.h"
# include "envptr.h"
# include "ast.h"
# include "free.h"
# include "redir.h"
# include "exec.h"

// splash screen colors
// \033[0m supostamente reseta o texto todo (https://ansi.tools/lookup) -- testar!!!
# define TXT_BOLD "\033[1m"
# define BOLD_RESET "\033[22m"
# define TXT_PINK "\033[35m"
# define TXT_BLACK "\033[30m"
# define TXT_YELLOW "\033[33m"
# define TXT_BLUE "\033[34m"
# define TXT_RESET "\033[39m"
# define BG_BLUE "\033[44m"
# define BG_WHITE "\033[47m"
# define BG_RESET "\033[49m"

// main.c
void	repl(char **envp, char *flag);

// Core - core.c
t_core	init_core(void);

// Wrapper functions - wrapper_*.c
void	*wr_calloc(size_t nmemb, size_t size, t_core *core);

// Exit handling - exit.c
void	exit_ts(t_core *core);
void	prt_n_bounce(char *msg, t_core *core);

// Signal handler - signal_handler.c
void	handle_sigint(int	signo);
void	handle_sigquit(int signo);
void	setup_signals(void);

// Utils - utils.c
//size_t	ft_strlen(char	*str);
bool	is_alpha(char c);
bool	is_digit(char c);
bool	is_identi(char c);
bool	is_metachar(char c);

//splash screen
void	show_title(void);

//prompt
void	get_prompt(t_core *core);

#endif
