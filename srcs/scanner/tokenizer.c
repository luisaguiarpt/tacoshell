#include "../headers/tacoshell.h"

t_token	create_token(t_token_type type, t_scanner *scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.length = (int)(scanner->current - scanner->start);
	if (type == STRING_DQ || type == STRING_SQ)
	{
		token.start++;
		token.length -= 2;
	}
	token.prev = NULL;
	token.next = NULL;
	return (token);
}

t_token	error_token(char *msg)
{
	t_token	token;

	token.type = ERROR_TOK;
	token.start = msg;
	token.length = (int)ft_strlen(msg);
	return (token);
}

void	append_token(t_token **head, t_token *new)
{
	t_token *tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
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
