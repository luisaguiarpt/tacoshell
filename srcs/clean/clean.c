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
	free(cmd->cmd_path);
	free_array(cmd->argv);
	clean_redirs(*cmd->redirs);
	free(cmd->redirs);
	free(cmd);
}

void	clean_ast(t_ast *node)
{
	if (node->type == PIPE_NODE)
	{
		if (node->left)
			clean_ast(node->left);
		if (node->right)
			clean_ast(node->right);
		free(node);
	}
	else
	{
		clean_ast_cmd(node->cmd);
		free(node);
	}
}

