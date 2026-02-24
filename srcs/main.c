#include "../headers/tacoshell.h"

void	start_scanner(t_core *core);

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
		if (!*core.line)
			continue ;
		if (*core.line)
			add_history(core.line);
		eval(&core, flag);
		clean_scanner(&core);
		clean_ast(&core);
	}
	full_free(&core);
	rl_clear_history();
	return (core.exit_status);
}

void	eval(t_core *core, char *flag)
{
	expand(core);
	start_scanner(core);
	link_tok(core->scanner, flag);
	check_syntax(core);
	if (core->syntax_error)
		return ;
	core->ast_root = create_ast(core);
	debug_ast(core->ast_root, flag);
	exec_control(core->ast_root, core);
}

void	start_scanner(t_core *core)
{
	core->scanner = init_scanner(core);
	core->syntax_error = false;
	core->tok_head = wr_calloc(1, sizeof(t_token *), core);
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
