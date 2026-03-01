#include "../headers/tacoshell.h"

static bool	check_syntax_empty(t_core *core);
static bool	check_syntax_pipe_start(t_token **head);
static bool	check_syntax_pipe_end(t_token **head);

void	check_syntax(t_core *core)
{
	t_token	**head;

	if (check_syntax_empty(core))
		;
	head = core->tok_head;
	if (check_syntax_pipe_start(head) || check_syntax_pipe_end(head))
	{
		core->exit_status = 2;
		core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, " syntax error near unexpected token `|'\n");
	}
}

// Return true if bad syntax
static bool	check_syntax_empty(t_core *core)
{
	if (core->line[0] == 0)
	{
		core->exit_status = 0;
		core->syntax_error = true;
		return (true);
	}
	return (false);
}

static bool	check_syntax_pipe_start(t_token **head)
{
	if ((*head)->type == PIPE)
		return (true);
	return (false);
}

static bool	check_syntax_pipe_end(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == PIPE)
		return (true);
	return (false);
}
