#include "../headers/tacoshell.h"

static int check_access(char *dir_path)
{
	if (access(dir_path, F_OK) != 0) //F_OK flag - check exxistence
	{
    	perror("Error");
		return(1);
	}
	if (access(dir_path, R_OK) != 0) //R_OK flag - check read access
	{
    	perror("Error");
		return(1);
	}
	return (0);
}

int ft_cd(t_core *core, char *dir_path)
{
	char	*new_path;
	char	tmp[PATH_MAX];

	if (check_access(dir_path) == 1)
		return (EXIT_FAILURE);
	if (chdir(dir_path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (!getcwd(tmp, sizeof(tmp)))
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	new_path = ft_strdup(tmp);
	if(core->old_pwd)
		free(core->old_pwd);
	core->old_pwd = ft_strdup(core->cwd);
	free(core->cwd);
	core->cwd = new_path;
	return (EXIT_SUCCESS);
}
