/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:13:43 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:13:44 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

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

void	free_tokens(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void	full_free(t_core *core)
{
	free_env(core);
	if (core->prompt)
		free(core->prompt);
	if (core->scanner)
		free(core->scanner);
	if (core->ast_root)
		clean_ast(core);
	if (core->tok_head)
	{
		free_tokens(*core->tok_head);
		free(core->tok_head);
	}
	core->exit_status = 0;
}
