#ifndef BUILTINS_H
# define BUILTINS_H

# include "tacoshell.h"

// Builtin commands
int		ft_cd(t_core *core, char **argv);
int		ft_echo(char **argv);
int		ft_pwd(t_core *core);
int		ft_env(t_core *core);
int		ft_export(t_core *core, char *argv);
int		ft_unset(t_core *core, char *arg);
void	ft_exit(t_core *core);

// Env
void	env_init(t_core *core, char **envp);
void	set_env(t_core *core, char *key, char *value);
char	*get_env(t_core *core, char *key);
int		unset_env(t_core *core, char *key);
void	env_split(char *env, char **key, char **value);

// Utils
int		count_args(char **argv);
void	exec_builtin(t_core *core, char **argv);
bool	is_builtin(char *cmd);

#endif
