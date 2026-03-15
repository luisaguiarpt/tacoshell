/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:45:38 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 19:53:51 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

void	free_tokens(t_token **node_ptr)
{
	t_token	*tmp;
	t_token	*node;

	if (!node_ptr)
		return ;
	node = *node_ptr;
	while (node)
	{
		tmp = node->next;
		free_token(node);
		node = tmp;
	}
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->word)
	{
		free(token->word);
		token->word = NULL;
	}
	if (token->mask)
	{
		free(token->mask);
		token->mask = NULL;
	}
	if (token->heredoc_delimiter)
	{
		free(token->heredoc_delimiter);
		token->heredoc_delimiter = NULL;
	}
	token->prev = NULL;
	token->next = NULL;
	free(token);
}

void	*free_mem_arr(char **arr, int index)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (i < index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
