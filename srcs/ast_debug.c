#include "../headers/tacoshell.h"

void	debug_ast(t_ast	*node, char *flag)
{
	if (!flag)
		return ;
	print_ast(node, 0, 0);
	printf("\n\nDETAILS:\n\n");
	print_ast_dfs(node);
}

// line: 0 (no line), 1 (right line), 2 (left line)
void	print_ast(t_ast *node, int depth, int line)
{
	int	i;

	if (!node)
		return;

	printf("\n\n\n");
	// Print right subtree first
	print_ast(node->right, depth + 1, 1);

	// Indentation
	for (i = 0; i < depth; i++)
		printf("         ");

	// Print current node
	if (line == 1)
		printf(" / ");
	else if (line == 2)
		printf(" \\ ");
	if (node->cmd && node->cmd->argv)
	{
		printf("%s (%d)\n", node->cmd->argv[0], node->type);

	}
	else
		printf("[PIPE %d]\n", node->type);

	// Print left subtree
	print_ast(node->left, depth + 1, 2);
}

void	print_ast_cmds(t_ast *node)
{
	char	**av = node->cmd->argv;
	int i = 0;

	printf("[NODE %d]\n", node->type);
	printf("CMD PATH:\n");
	printf("\t%s\n", node->cmd->cmd_path);
	printf("ARGS:\n");
	while (av && av[i])
	{
		printf("%s,", av[i]);
		i++;
	}
	printf("\n");
}

void	print_ast_redirs(t_ast *node)
{
	printf("REDIRS:\n");
	t_redir	**curr = node->cmd->redirs;

	while (*curr)
	{
		printf("\tTYPE: %d | PATH: %s\n", (*curr)->type, (*curr)->file_path);
		*curr = (*curr)->next;
	}
}

void	print_ast_dfs(t_ast *node)
{
	if (!node)
		return;

	// Visit node
	if (node->cmd)
	{
		print_ast_cmds(node);
		print_ast_redirs(node);
	}
	else
		printf("[NODE %d]\n\n", node->type);

	// Traverse children
	print_ast_dfs(node->left);
	print_ast_dfs(node->right);
}
