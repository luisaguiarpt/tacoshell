/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:06 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:16:08 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

t_redir	*redir_new(t_token_type	type, char *file_path)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type= type;
	node->file_path = file_path;
	node->next = NULL;
	return (node);
}

void	redir_append(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = redir_last(*lst);
	last->next = new;
}

void	redir_clean(t_redir **lst)
{
	t_redir	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->file_path)
			free((*lst)->file_path);
		free(*lst);
		*lst = tmp;
	}
}

t_redir	*redir_last(t_redir *lst)
{
	t_redir	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	while (ptr->next != 0)
		ptr = ptr->next;
	return (ptr);
}
