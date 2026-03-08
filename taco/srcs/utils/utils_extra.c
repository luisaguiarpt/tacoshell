#include "../incs/minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

bool	is_op_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (true);
	return (false);
}
