#include "../headers/tacoshell.h"

static bool	check_syntax_empty(t_core *core);
static bool	check_syntax_pipe(t_token **head);
static bool	check_syntax_pipe_end(t_token **head);
static bool	check_syntax_redir(t_core *core);
static bool	check_syntax_words(t_core *core);

void	check_syntax(t_core *core)
{
	t_token	**head;

	if (check_syntax_empty(core))
		return ;
	if (check_syntax_words(core))
		return ;
	if (check_syntax_redir(core))
	{
		core->exit_status = 2;
		core->syntax_error = true;
		ft_printf_fd(2, "syntax error: unexpected redirection operators\n");
		return ;
	}
	head = core->tok_head;
	if (check_syntax_pipe(head) || check_syntax_pipe_end(head))
	{
		core->exit_status = 2;
		core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `|'\n");
	}
}

static bool	check_syntax_words(t_core *core)
{
	int		word_count;
	t_token	*tmp;

	word_count = 0;
	tmp = *core->tok_head;
	while (tmp)
	{
		if (tmp->type == WORD)
			word_count++;
		tmp = tmp->next;
	}
	if (!word_count)
	{
		core->exit_status = 2;
		core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, "syntax error\n");
		return (true);
	}
	return (false);
}

// Returns true if redir op without a word after
// Returns true if two redirs in a row
static bool	check_syntax_redir(t_core *core)
{
	t_token	*tmp;

	tmp = *core->tok_head;
	while (tmp && tmp->next)
	{
	    if (tmp->type >= 5 && tmp->type <= 8
				&& tmp->next->type >= 5 && tmp->next->type <= 8)
			return (true);
		if (tmp->type >= 5 && tmp->type <= 8 && tmp->next->type != WORD)
			return (true);
		tmp = tmp->next;
	}
	return (false);
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

// Returns true if pipe at start
// Returns true two pipes in a row
static bool	check_syntax_pipe(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	if ((*head)->type == PIPE)
		return (true);
	while (tmp && tmp->next)
	{
		if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (true);
		tmp = tmp->next;
	}
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
