#ifndef BUILTINS_H
# define BUILTINS_H

# include "tacoshell.h"

typedef struct	s_env t_env;

typedef struct	s_env
{
	char		*key;
	char		*value;
	t_env		*next;
}				t_env;

// Builtin commands
int	ft_cd(t_core *core, char *dir_path);
int	ft_echo(int nflag, char *arg);
int	ft_pwd(t_core *core);
int	ft_env(t_core *core);

// Env
void	env_init(t_core *core, char **envp);
void	set_env(t_core *core, char *key, char *value);
char	*get_env(t_core *core, char *key);
int		unset_env(t_core *core, char *key);
void	env_split(char *env, char **key, char **value);

#endif
