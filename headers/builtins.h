#ifndef BUILTINS_H
# define BUILTINS_H

# include "tacoshell.h"

// Builtin commands
// exit -> exit_ts ([...].h)
int		ft_cd(t_core *core, char *dir_path);
int		ft_echo(char **argv);
int		ft_pwd(t_core *core);
int		ft_env(t_core *core);
int		ft_export(t_core *core, char *argv);
int		ft_unset(t_core *core, char *arg);

// Env
void	env_init(t_core *core, char **envp);
void	set_env(t_core *core, char *key, char *value);
char	*get_env(t_core *core, char *key);
int		unset_env(t_core *core, char *key);
void	env_split(char *env, char **key, char **value);

// Utils
void	exec_builtin(t_core *core, char *cmd, char **argv);
int		is_builtin(char *cmd);

#endif
