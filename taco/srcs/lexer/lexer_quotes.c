#include "../incs/minishell.h"

void	upd_rd_state(t_token *token, t_state state, size_t *rd)
{
	token->state = state;
	*rd = *rd + 1;
}

void	read_write_token(t_token *token, size_t *rd, size_t *wr)
{
	token->word[*wr] = token->word[*rd];
	token->mask_exp[*wr] = token->mask_exp[*rd];
	*wr = *wr + 1;
	*rd = *rd + 1;
}
