/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:05:29 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:05:38 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Changes state and returns true if state changed and false if not
bool	get_state(char c, t_state *state)
{
	if (c == '\'' && *state == NEUTRAL)
	{
		*state = IN_SINGLE_QUOTES;
		return (true);
	}
	else if (c == '\'' && *state == IN_SINGLE_QUOTES)
	{
		*state = NEUTRAL;
		return (true);
	}
	else if (c == '"' && *state == NEUTRAL)
	{
		*state = IN_DOUBLE_QUOTES;
		return (true);
	}
	else if (c == '"' && *state == IN_DOUBLE_QUOTES)
	{
		*state = NEUTRAL;
		return (true);
	}
	return (false);
}

char	*rm_quotes(char *str, t_shell *shell)
{
	int		i;
	int		k;
	t_state	state;
	char	*tmp;

	i = 0;
	k = 0;
	state = NEUTRAL;
	tmp = wr_calloc(1, ft_strlen(str) + 1, shell);
	while (str[i])
	{
		if (get_state(str[i], &state))
		{
			i++;
			continue ;
		}
		else
			tmp[k++] = str[i++];
	}
	tmp[k] = 0;
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

t_token	*find_lowest_prec(t_token *start, t_token *end)
{
	t_token	*lowest;
	t_token	*token;
	int		prec;
	int		min_prec;

	lowest = NULL;
	min_prec = INT_MAX;
	token = start;
	while (end && token != end->next)
	{
		if (is_pipe(*token))
		{
			prec = precedence(*token);
			if (prec <= min_prec)
			{
				min_prec = prec;
				lowest = token;
			}
		}
		token = token->next;
	}
	return (lowest);
}
