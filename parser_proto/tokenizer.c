#include "tacoshell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	**ft_split(char const *s, char c);

int	main(int ac, char **av)
{
	char	*line;
	char	**split_line;
	int		i;

	line = readline("$> ");
	split_line = ft_split(line, ' ');
	i = 0;
	while (split_line[i])
	{
		printf("%s\n", split_line[i]);
		i++;
	}
}
