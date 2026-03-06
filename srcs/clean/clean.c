/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:10:36 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:10:39 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

void	clean_scanner(t_core *core)
{
	free_tokens(*core->tok_head);
	if (core->tok_head)
		free(core->tok_head);
	core->tok_head = NULL;
	if (core->scanner)
		free(core->scanner);
	core->scanner = NULL;
	if (core->line)
		free(core->line);
	core->line = NULL;
}

void	clean_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		free(redir->file_path);
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}

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

void	clean_ast(t_core *core)
{
	clean_ast_node(core->ast_root);
	core->ast_root = NULL;
}
