#include "../headers/tacoshell.h"

int	is_builtin(char *cmd)
{
	if (cmd == "echo" || cmd == "cd" || cmd == "pwd" || cmd == "export"
		|| cmd == "unset" || cmd == "env" || cmd == "exit")
		return (1);
	else
		return (0);
}

/*
 * echo -> ft_echo
 * cd = ft_cd
 * pwd = ft_pwd
 * export = set_env
 * unset = unset_env
 * env = ft_env
 * exit = exit_ts
 */

void	exec_builtin(t_core *core, char **prompt)
{

}
