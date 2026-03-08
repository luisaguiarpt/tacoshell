#ifndef DEBUG_H
# define DEBUG_H

// debug.c - Debug functions
void	set_shell_debug(t_shell *shell, char **av);
void	print_env_var(t_shell *shell);
void	print_tokens(t_shell *shell);
void	print_token_type(t_token *token);

#endif

