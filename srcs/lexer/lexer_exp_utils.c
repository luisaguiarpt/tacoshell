#include "../incs/minishell.h"

void	upd_exp_mask(t_token *token, int i, char *key, char *value)
{
	char	*new_mask;
	size_t	start;
	size_t	new_end;
	size_t	old_end;
	size_t	new_len;

	start = i;
	new_end = i + ft_strlen(value);
	old_end = i + ft_strlen(key);
	new_len = ft_strlen(token->word);
	new_mask = ft_calloc(1, sizeof(char) * (new_len + 1));
	if (!new_mask)
		return ;
	ft_memmove(new_mask, token->mask, start);
	while (start < new_end)
		new_mask[start++] = '1';
	ft_memmove(&new_mask[new_end], &token->mask[old_end], new_len - new_end);
	free(token->mask);
	token->mask = new_mask;
}

void	upd_tok_state(char c, t_token *token)
{
	if (c == '\'' && token->state == NEUTRAL)
		token->state = IN_SQ;
	else if (c == '\'' && token->state == IN_SQ)
		token->state = NEUTRAL;
	else if (c == '"' && token->state == NEUTRAL)
		token->state = IN_DQ;
	else if (c == '"' && token->state == IN_DQ)
		token->state = NEUTRAL;
}

char	*set_expansion_mask(t_shell *shell, t_token *token)
{
	char	*mask;
	size_t	len;
	size_t	i;
	
	len = ft_strlen(token->word);
	mask = ft_calloc(1, (len + 1) * sizeof(char));
	if (!mask)
		exit_clean(shell, EXIT_FAILURE);
	i = 0;
	while (i < len)
		mask[i++] = '0';
	return (mask);
}
