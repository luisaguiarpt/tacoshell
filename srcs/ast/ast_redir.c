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

#include "../../incs/minishell.h"

void	add_redir_node(t_ast_cmd *cmd, t_token *token, t_shell *shell)
{
	char	*filename;
	t_redir	*new_node;

	(void)shell;
	filename = token->next->word;
	new_node = redir_new(token->type, filename, token->heredoc_delimiter);
	redir_append(cmd->redirs, new_node);
}
