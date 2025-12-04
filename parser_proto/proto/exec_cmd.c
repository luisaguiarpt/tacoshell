#include "../../headers/tacoshell.h"

void	exec_cmd(char *prompt, t_core *core)
{
	if (prompt[0] == 'e' && prompt[1] == 'c')
	{
		if (prompt[5] == '-')
			ft_echo(1, &prompt[8]);
		else 
			ft_echo(0, &prompt[5]);
	}
	else if (prompt[0] == 'e' && prompt [1] == 'n')
		ft_env(core);
	else if (prompt[0] == 'c')
		ft_cd(core, &prompt[3]);
	else if (prompt[0] == 'p')
		ft_pwd(core);
	return ;
}
