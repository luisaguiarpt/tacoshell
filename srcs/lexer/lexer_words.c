#include "../incs/minishell.h"

int	replace_dollar(t_shell *shell, t_token *token, int i)
{
	char	*tmp_value;

	if (token->word[i] == '$' && token->word[i + 1] == '?')
	{
		tmp_value = ft_itoa(shell->exit_status);
		token->word = str_replace(shell, token->word, "$?", tmp_value);
		upd_exp_mask(token, i, "$?", tmp_value);
		i = ft_strlen(tmp_value);
		free(tmp_value);
	}
	else if (token->word[i] == '$')
		i = replace_dollar_var(shell, token, i);
	return (i);
}

int	replace_dollar_var(t_shell *shell, t_token *token, int i)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = parse_var_name(&token->word[i]);
	tmp_value = get_var_value(shell, &tmp_key[1]);
	if (!ft_strcmp(tmp_key, "$"))
		return (++i);
	if (tmp_value)
	{
		token->word = str_replace(shell, token->word, tmp_key, tmp_value);
		upd_exp_mask(token, i, tmp_key, tmp_value);
		i = ft_strlen(tmp_value);
	}
	else
	{
		token->word = str_replace(shell, token->word, tmp_key, "");
		upd_exp_mask(token, i, tmp_key, "");
		i = ft_strlen("");
	}
	free(tmp_key);
	return (i);
}

char	*parse_var_name(char *line)
{
	char	*word;
	size_t	i;
	size_t	k;

	i = 0;
	if (!line)
		return (NULL);
	while ((line[i] && is_posix_var(line[i])) || (i == 0 && line[i] == '$'))
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	k = 0;
	while (k < i)
	{
		word[k] = line[k];
		k++;
	}
	word[i] = 0;
	return (word);
}

char	*get_word_from_lexer(t_shell *shell)
{
	t_lexer	*lexer;
	char	*word;
	size_t	len;

	lexer = shell->lexer;
	len = (int)(lexer->current - lexer->start);
	word = ft_substr(lexer->start, 0, len);
	if (!word)
		exit_clean(shell, EXIT_FAILURE);
	return (word);
}
