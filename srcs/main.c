#include "../headers/tacoshell.h"

void	print_tok(t_token *head);
void	link_tok(t_scanner *scanner, char *flag);
void	start_scanner(t_core *core);
void	clean_scanner(t_core *core);

int	main(int ac, char **av, char **envp)
{
	int	exit_code;

	(void)av;
	//show_title();
	//if (ac == 1)
	(void)ac;
	exit_code = repl(envp, av[1]);
	/*
	else if (ac > 1)
	{
		printf("Usage: ./minishell\n");
		exit(EINVAL);
	}
	*/
	return (exit_code);
}

int	repl(char **envp, char	*flag)
{
	t_core	core;

	setup_signals();
	core = init_core();
	env_init(&core, envp);
	while (true)
	{
		get_prompt(&core);
		core.line = readline(core.prompt);
		if (!core.line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*core.line)
			add_history(core.line);
		start_scanner(&core);
		link_tok(core.scanner, flag);
		core.ast_root = create_ast(&core);
		debug_ast(core.ast_root, flag);
		exec_control(core.ast_root, &core);
		clean_scanner(&core);
		// FUNCTION TO 
	}
	full_free(&core);
	rl_clear_history();
	return (core.exit_status);
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

void	link_tok(t_scanner *scanner, char *flag)
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
	if (!flag)
		return ;
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
