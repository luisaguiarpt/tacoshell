#ifndef SHELL_H
# define SHELL_H

// shell_init.c - shell struct initialization
t_shell	init_shell(char **av, char **ep);
void	set_shell_null(t_shell *shell);

#endif
