#include "../../headers/tacoshell.h"

void	print_tok(t_token *head);
void	link_tok(t_scanner *scanner);
void	start_scanner(t_core *core);
void	clean_scanner(t_core *core);
void	repl(char **envp);

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		repl(envp);
	else if (ac > 1)
	{
		printf("Usage: ./minishell\n");
		exit(EINVAL);
	}
	return (EXIT_SUCCESS);
}

void	repl(char **envp)
{
	t_core	core;

	setup_signals();
	core = init_core();
	env_init(&core, envp);
	while (true)
	{
		core.line = readline(get_env(&core, "PWD"));
		if (!core.line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*core.line)
			add_history(core.line);
		exec_cmd(core.line, &core);
		start_scanner(&core);
		link_tok(core.scanner);
		clean_scanner(&core);
	}
	rl_clear_history();
}

void	start_scanner(t_core *core)
{
	core->scanner = init_scanner(core);
	core->tok_head = wr_calloc(1, sizeof(t_token *), core);
}

void	clean_scanner(t_core *core)
{
	free_tokens(*core->tok_head);
	free(core->tok_head);
	core->tok_head = NULL;
	free(core->scanner);
	free(core->line);
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
		printf("\n----\n %2d '%.*s'\n", head->type, (int)head->length, head->start);
		printf("Prev: %p | Curr: %p | Next: %p\n", head->prev, head, head->next);
		if (head->type == EOF_TOK)
			break;
		head = head->next;
	}
}
