#include "tacoshell.h"

int	shell_status = 1;

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		repl();
	else if (ac > 1)
	{
		printf("Usage: ./minishell\n");
		exit(EX_USAGE);
	}
	return (EXIT_SUCCESS);
}

void	repl(void)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = readline("$> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*line)
			add_history(line);
		
		free(line);
	}
}
