#include "../headers/tacoshell.h"

void	clean_scanner(t_core *core)
{
	free_tokens(*core->tok_head);
	free(core->tok_head);
	core->tok_head = NULL;
	free(core->scanner);
	free(core->line);
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
			clean_ast_node(node->left);
		if (node->right)
			clean_ast_node(node->right);
	}
	else
	{
		clean_ast_cmd(node->cmd);
		node->cmd = NULL;
	}
}

void	clean_ast(t_core *core)
{
	clean_ast_node(core->ast_root);
	free(core->ast_root);
	core->ast_root = NULL;
}

