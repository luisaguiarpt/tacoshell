#include "tacoshell.h"

void	print_tok(t_token *head);
void	link_tok(t_scanner *scanner);
void	start_scanner(t_core *core);
void	clean_scanner(t_core *core);
void	repl(void);
char	*set_cwd(void);

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
		char	*current_dir;

		current_dir = set_cwd();
		core.line = readline(current_dir);
		if (!core.line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*core.line)
			add_history(core.line);
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

char	*set_cwd(void)
{
		char	cwd_result[PATH_MAX];
		char	*current_dir;

		getcwd(cwd_result, sizeof(cwd_result));
		current_dir = malloc((ft_strlen(cwd_result) + 4));
		current_dir = ft_strjoin(cwd_result, " $> ");
		return (current_dir);
}
