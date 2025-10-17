#include "tacoshell.h"

t_token	create_token(t_token_type type, t_scanner *scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.length = (int)(scanner->current - scanner->start);
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
