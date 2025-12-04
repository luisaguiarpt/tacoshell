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
	char	*current_path;
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

	current_path = get_env(core, "PWD");
	set_env(core, "PWD", tmp);
	set_env(core, "OLDPWD", current_path);
	return (EXIT_SUCCESS);
}
