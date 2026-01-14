#include "../headers/tacoshell.h"

bool	is_operator(t_token token);
bool	is_operator(t_token token);
t_token	*find_lowest_prec(t_token *start, t_token *end);

t_ast	create_ast(t_core)
{
	t_token	*start;
	t_token	*end;
	t_ast	ast;

	start = *core->tok_head;
	end = start;
	while (end->next)
		end = end->next;
	ast = parse_tokens(start, end);
	return (ast);
}

// Need a function to create a node out of an operator
// and then a function to create a node out of a chain of tokens (commands)
t_ast	*parse_tokens(t_token *start, t_token *end)
{
	t_token	*op;
	t_ast	node;

	op = find_lowest_prec(start, end);
	if (!op)
		return (create_node(CMD, start, end));
	else
		return (create_node(PIPE, start, end));
	node = create_node(op);
}

t_ast	*create_node(t_token_type type, t_token *start, t_token *end)
{
	t_ast	*node;

	node = wr_calloc(1, sizeof(t_ast), core);
	node->type = type;
	if (type == CMD)
	{
		node->args = gen_args(start, end);
	return (node);
}

t_token	*find_lowest_prec(t_token *start, t_token *end)
{
	t_token *lowest;
	t_token *token;
	int		prec;
	int		min_prec;

	lowest = NULL;
	min_prec = INT_MAX;
	token = start;
	while (token != end->next)
	{
		if (is_operator(&token))
		{
			prec = precedence(&token);
			if (prec <= min_prec)
			{
				min_prec = prec;
				lowest = t;
			}
		}
	}
	return (lowest);
}

bool	is_operator(t_token token)
{
	if (token.type == REDIR_OUT || token.type == REDIR_IN || token.type == PIPE)
		return (true);
	if (token.type == APPEND || token.type == HERE_DOC)
		return (true);
	return (false);
}

bool	precedence(t_token token)
{
	if (token.type == PIPE)
		return (2);
	if (token.type == REDIR_IN || token.type == REDIR_OUT)
		return (3);
	if (token.type == APPEND || token.type == HERE_DOC)
		return (3);
	else
		return (4);
}
