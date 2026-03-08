#include "../incs/minishell.h"

void	upd_exp_mask(t_token *token, int i, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len--)
		token->mask_exp[i - len] = 1;
}

void	upd_tok_state(char c, t_token *token)
{
	if (c == '\'' && token->state == NEUTRAL)
		token->state = IN_SINGLE_QUOTES;
	else if (c == '\'' && token->state == IN_SINGLE_QUOTES)
		token->state = NEUTRAL;
	else if (c == '"' && token->state == NEUTRAL)
		token->state = IN_DOUBLE_QUOTES;
	else if (c == '"' && token->state == IN_DOUBLE_QUOTES)
		token->state = NEUTRAL;
}

char	*set_expansion_mask(t_shell *shell, t_token *token)
{
	char	*mask_exp;
	size_t	len;
	
	len = ft_strlen(token->word);
	mask_exp = ft_calloc(1, (len + 1) * sizeof(char));
	if (!mask_exp)
		exit_clean(shell, EXIT_FAILURE);
	return (mask_exp);
}
