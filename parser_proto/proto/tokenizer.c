#include "../../headers/tacoshell.h"

t_token	create_token(t_token_type type, t_scanner *scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.length = (int)(scanner->current - scanner->start);
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

void	free_tokens(t_token *head)
{
    t_token *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}
