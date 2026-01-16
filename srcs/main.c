#include "../headers/tacoshell.h"

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
		// line below needs to be tought out because of leaks
		core.line = readline(ft_strjoin(get_env(&core, "PWD"), " › "));
		if (!core.line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*core.line)
			add_history(core.line);
		start_scanner(&core);
		link_tok(core.scanner);
		core.ast_root = create_ast(&core);
		printf("\n\n\n");
		print_ast(core.ast_root, 0, 0);
		printf("\n\nDETAILS:\n\n");
		print_ast_dfs(core.ast_root);
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
	t_token *tmp;

	tmp = head;
	while (head)
	{
		printf("\n----\n %2d '%.*s'\n", tmp->type, (int)tmp->length, tmp->start);
		printf("Prev: %p | Curr: %p | Next: %p\n", tmp->prev, tmp, tmp->next);
		if (tmp->type == EOF_TOK)
			break;
		tmp = tmp->next;
	}
}
