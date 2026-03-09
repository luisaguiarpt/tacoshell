#include "../incs/minishell.h"

void	expansion(t_shell *shell, t_token **token)
{
	var_expansion(shell, token);
	word_split(shell, *token);
	quote_remove(shell, *token);
}

void	quote_remove(t_shell *shell, t_token *token)
{
	size_t	read;
	size_t	write;
	t_state	state;

	if (!token || !token->word || !token->mask_exp)
		return ;
	read = 0;
	write = 0;
	state = NEUTRAL;
	while (token->word[read])
	{
		if (token->mask_exp[read] == '0' && token->word[read] == '"' && state == NEUTRAL)
		{
			state = IN_DQ;
			read++;
		}
		else if (token->mask_exp[read] == '0' && token->word[read] == '"' && state == IN_DQ)
		{
			state = NEUTRAL;
			read++;
		}
		else if (token->mask_exp[read] == '0' && token->word[read] == '\'' && state == NEUTRAL)
		{
			state = IN_SQ;
			read++;
		}
		else if (token->mask_exp[read] == '0' && token->word[read] == '\'' && state == IN_SQ)
		{
			state = NEUTRAL;
			read++;
		}
		else
		{
			token->word[write] = token->word[read];
			token->mask_exp[write] = token->mask_exp[read];
			write++;
			read++;
		}
	}
	token->word[write] = '\0';
	token->mask_exp[write] = '\0';
	(void)shell;
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
		if (token->word[i] == ' ' && token->mask_exp[i] == 1)
		{
			new_token = split_token(shell, token, i);
			append_token(shell, new_token);
			i = 0;
		}
		else
			i++;
	}
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
	new_mask = ft_substr(token->mask_exp, i + 1, ft_strlen(token->mask_exp) - (i + 1));
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
