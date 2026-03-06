/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:04:57 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:05:08 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

char	*prep_filename(t_token *start)
{
	char	*tmp;
	char	*filename;

	tmp = ft_substr(start->next->start, 0, start->next->length);
	filename = ft_strtrim(tmp, "\"");
	free(tmp);
	return (filename);
}

void	add_redir_node(t_ast_cmd *cmd, t_token *start, t_core *core)
{
	char	*filename;
	t_redir	*new_node;

	(void)core;
	filename = prep_filename(start);
	filename = rm_quotes(filename, core);
	new_node = redir_new(start->type, filename);
	redir_append(cmd->redirs, new_node);
}
