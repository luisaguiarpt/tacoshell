#include "tacoshell.h"

/*
size_t	ft_strlen(char	*str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}
*/

bool	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

bool	is_identi(char c)
{
	if (is_alpha(c) || c == '.' || c == '-')
		return (true);
	return (false);
}

bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

void  set_cwd(t_core *core)
{
		char	cwd_result[PATH_MAX];
		char	*current_dir;

    if (core->cwd)
    {
      free(core->cwd);
      core->cwd = NULL;
    }
		getcwd(cwd_result, sizeof(cwd_result));
		current_dir = ft_strjoin(cwd_result, " $> ");
		core->cwd = current_dir;
    return ;
}
