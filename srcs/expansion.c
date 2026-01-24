#include "../headers/tacoshell.h"

static bool	is_inside_squotes(char *line, bool prev_inside_sq);
static char	*isolate_word(char *line);
static char	*replace_str(char *s, char *old, char *new);

// inside_sq is a flag that records whether the pointer is currently within single quotes
// 0 -> outside single quotes; 1 -> inside single quotes
// We'll expand the $VAR in the same manner whether it's inside double quotes or not
void	expand(t_core *core)
{
	int		i;
	bool	inside_sq;
	char	*tmp;

	i = 0;
	inside_sq = false;
	while (core->line && core->line[i])
	{
		inside_sq = is_inside_squotes(core->line, inside_sq);
		if (!inside_sq && core->line[i] == '$' && core->line[i + 1] == '?')
		{
			tmp = ft_itoa(core->exit_status);
			core->line = replace_str(core->line, "$?", tmp);
			free(tmp);
		}
		else if (!inside_sq && core->line[i] == '$')
		{
			tmp = isolate_word(&(core->line[i]));
			core->line = replace_str(core->line, tmp, get_env(core, &tmp[1]));
			free(tmp);
		}
		i++;
	}
}

// Substitute an occurence of 'old' within 'str' with 'new'
// Frees the original string, hence the replace
static char	*replace_str(char *s, char *old, char *new)
{
	size_t	new_s_len;
	size_t	i;
	size_t	j;
	char	*new_str;

	//if (ft_strlen(old) == 0)
	//	return (s);
	new_s_len = ft_strlen(s) - ft_strlen(old) + ft_strlen(new);
	new_str = ft_calloc(new_s_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (ft_strncmp(&s[j], old, ft_strlen(old)) == 0)
		{
			j += ft_strlen(old);
			while (*new)
				new_str[i++] = *new++;
		}
		else
			new_str[i++] = s[j++];
	}
	//new_str[i] = 0;
	free(s);
	return (new_str);
}

// Returns a malloc'd char * of a single word (delimited by an ending space)
static char	*isolate_word(char *line)
{
	char	*word;
	size_t	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line && line[i] && line[i] != ' ')
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (line[i])
	{
		word[i] = line[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static bool	is_inside_squotes(char *line, bool prev_inside_sq)
{
	bool	inside_sq;

	inside_sq = prev_inside_sq;
	if (*line == '\'' && !prev_inside_sq)
		inside_sq = true;
	else if (*line == '\'' && prev_inside_sq)
		inside_sq = false;
	return (inside_sq);
}
/*
int	main(void)
{
	char	*str = "echo $VAR1 world";
	char	*old = "$VAR1";
	char	*new = "Beautiful";

	printf("String: %s\n", str);
	printf("Old: %s\n", old);
	printf("New: %s\n", new);
	char	*new_str = replacestr(str, old, new);
	printf("New String: %s\n", new_str);
}
*/
