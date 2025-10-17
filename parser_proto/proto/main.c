#include "tacoshell.h"

void	print_tok(t_token *head);
void	link_tok(t_scanner *scanner);

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
	while (true)
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
		link_tok(core.scanner);
		free(core.line);
	}
}

void	link_tok(t_scanner *scanner)
{
	t_token	*token;

	while (1)
	{
		token = wr_calloc(1, sizeof(t_token), scanner->core);
		*token = scan_token(scanner);
		append_token(scanner->core->tok_head, token);
		if (token->type == EOF_TOK)
			break;
	}
	print_tok(*scanner->core->tok_head);
}

void	print_tok(t_token *head)
{
	while (head)
	{
		printf("%2d '%.*s'\n", head->type, (int)head->length, head->start);
		if (head->type == EOF_TOK)
			break;
		head = head->next;
	}
}
