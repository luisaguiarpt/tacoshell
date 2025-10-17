#include "tacoshell.h"

void	print_tok(t_scanner *scanner);

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		repl();
	else if (ac > 1)
	{
		printf("Usage: ./minishell\n");
		exit(EINVAL);
	}
	return (EXIT_SUCCESS);
}

void	repl(void)
{
	t_core	core;

	setup_signals();
	core = init_core();
	while (1)
	{
		core.line = readline("$> ");
		if (!core.line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*core.line)
			add_history(core.line);
		core.scanner = init_scanner(&core);
		print_tok(core.scanner);
		free(core.line);
	}
}

void	print_tok(t_scanner *scanner)
{
	while (1)
	{
		t_token	token = scan_token(scanner);
		printf("%2d '%.*s'\n", token.type, (int)token.length, token.start);
		if (token.type == EOF_TOK)
			break;
	}
}
