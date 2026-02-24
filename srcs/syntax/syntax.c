#include "../headers/tacoshell.h"

static bool	check_syntax_pipe_start(t_token **head);
static bool	check_syntax_pipe_end(t_token **head);

// Returns false if bad syntax
void	check_syntax(t_core *core)
{
	t_token	**head;

	head = core->tok_head;
	if (check_syntax_pipe_start(head) || check_syntax_pipe_end(head))
	{
		core->exit_status = 2;
		core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, " syntax error near unexpected token `|'\n");
	}
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
