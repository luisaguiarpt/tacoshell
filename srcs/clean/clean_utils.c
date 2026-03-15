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

void	clean_ast_cmd(t_ast_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	cmd->cmd_path = NULL;
	if (cmd->argv)
		free_array(cmd->argv);
	cmd->argv = NULL;
	clean_redirs(*cmd->redirs);
	free(cmd->redirs);
	cmd->redirs = NULL;
	free(cmd);
}

void	clean_ast_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == PIPE_NODE)
	{
		if (node->left)
		{
			clean_ast_node(node->left);
			node->left = NULL;
		}
		if (node->right)
		{
			clean_ast_node(node->right);
			node->right = NULL;
		}
		free(node);
	}
	else
	{
		clean_ast_cmd(node->cmd);
		node->cmd = NULL;
		free(node);
	}
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

void	clean_shell_vars(t_shell *shell)
{
	t_variable	*var;
	t_variable	*tmp;

	var = *shell->vars;
	while (var)
	{
		tmp = var->next;
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		if (var->exportstr)
			free(var->exportstr);
		free(var);
		var = tmp;
	}
	free(shell->vars);
}
