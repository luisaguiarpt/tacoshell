#include "../incs/minishell.h"

void	expansion(t_shell *shell, t_token **token)
{
	var_expansion(shell, token);
	word_split(shell, *token);
	quote_remove(shell, *token);
}

void	var_expansion(t_shell *shell, t_token **token)
{
	int	i;

	if ((*token)->has_dollar == 0)
		return ;
	i = 0;
	while ((*token)->word && (*token)->word[i])
	{
		upd_tok_state((*token)->word[i], (*token));
		if ((*token)->state == IN_SQ)
			i++;
		else if ((*token)->word[i] == '$')
			i += replace_dollar(shell, *token, i);
		else
			i++;
	}
	if ((*token)->has_dollar && !ft_strlen((*token)->word))
	{
		remove_token(shell, *token);
		*token = NULL;
	}
}

void	word_split(t_shell *shell, t_token *token)
{
	t_token			*new_token;
	int				i;

	i = 0;
	if (!token)
		return ;
	while (token->word && token->word[i])
	{
		if (token->word[i] == ' ' && token->mask[i] == 1)
		{
			new_token = split_token(shell, token, i);
			append_token(shell, new_token);
			i = 0;
		}
		else
			i++;
	}
}

void	quote_remove(t_shell *shell, t_token *t)
{
	size_t	rd;
	size_t	wr;

	if (!t || !t->word || !t->mask)
		return ;
	rd = 0;
	wr = 0;
	t->state = NEUTRAL;
	while (t->word[rd])
	{
		if (t->mask[rd] == '0' && t->word[rd] == '"' && t->state == NEUTRAL)
			upd_rd_state(t, IN_DQ, &rd);
		else if (t->mask[rd] == '0' && t->word[rd] == '"' && t->state == IN_DQ)
			upd_rd_state(t, NEUTRAL, &rd);
		else if (t->mask[rd] == '0' && t->word[rd] == '\'' && t->state == NEUTRAL)
			upd_rd_state(t, IN_SQ, &rd);
		else if (t->mask[rd] == '0' && t->word[rd] == '\'' && t->state == IN_SQ)
			upd_rd_state(t, NEUTRAL, &rd);
		else
			read_write_token(t, &rd, &wr);
	}
	t->word[wr] = '\0';
	t->mask[wr] = '\0';
	(void)shell;
}

t_token	*split_token(t_shell *shell, t_token *token, int i)
{
	t_token	*new_tok;
	char	*new_word;
	char	*new_mask;
	char	*tmp;

	new_word = ft_substr(token->word, i + 1, ft_strlen(token->word) - (i + 1));
	if (!new_word)
		exit_clean(shell, EXIT_FAILURE);
	new_mask = ft_substr(token->mask, i + 1, ft_strlen(token->mask) - (i + 1));
	if (!new_mask)
		exit_clean(shell, EXIT_FAILURE);
	new_tok = new_token(shell, new_word, TK_WORD);
	tmp = token->word;
	token->word = ft_substr(token->word, 0, i);
	if (!token->word)
		exit_clean(shell, EXIT_FAILURE);
	free(tmp);
	return (new_tok);
}
