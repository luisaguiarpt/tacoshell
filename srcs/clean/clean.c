#include "../../incs/minishell.h"

void	clean(t_shell *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->lexer)
		clean_lexer(shell);
	if (shell->ast_root)
		clean_ast(shell);
}
void	exit_clean(t_shell *shell, int exit_code)
{
	if (shell->prompt)
		free(shell->prompt);
	if (shell->line)
		free(shell->line);
	if (shell->vars)
		clean_shell_vars(shell);
	if (shell->lexer)
		clean_lexer(shell);
	if (shell->ast_root)
		clean_ast(shell);
	if (shell->env_ptr)
		free_array(shell->env_ptr);
	exit(exit_code);
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

void	clean_ast(t_shell *shell)
{
	clean_ast_node(shell->ast_root);
	shell->ast_root = NULL;
}

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

void	clean_lexer(t_shell *shell)
{
	t_token	*node;

	if (!shell->tokens)
		return ;
	node = *shell->tokens;
	(void)node;
	free_tokens(shell->tokens);
	free(shell->tokens);
	shell->tokens = NULL;
	free(shell->lexer);
	shell->lexer = NULL;
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
