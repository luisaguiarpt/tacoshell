#ifndef CLEAN_H
# define CLEAN_H

void	clean(t_shell *shell);
void	exit_clean(t_shell *shell, int exit_code);
void	clean_shell_vars(t_shell *shell);
void	clean_lexer(t_shell *shell);
void	free_token_list(t_token_list *node);

#endif
