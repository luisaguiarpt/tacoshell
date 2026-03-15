/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:02:14 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/09 15:02:15 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	debug_ast(t_ast	*node)
{
	print_ast(node, 0, 0);
	printf("\n\nDETAILS:\n\n");
	print_ast_dfs(node);
}

// line: 0 (no line), 1 (right line), 2 (left line)
void	print_ast(t_ast *node, int depth, int line)
{
	int	i;

	if (!node)
		return ;
	printf("\n\n\n");
	print_ast(node->right, depth + 1, 1);
	i = 0;
	while (i < depth)
	{
		printf("         ");
		i++;
	}
	if (line == 1)
		printf(" / ");
	else if (line == 2)
		printf(" \\ ");
	if (node->cmd && node->cmd->argv)
		printf("%s (%d)\n", node->cmd->argv[0], node->type);
	else
		printf("[PIPE %d]\n", node->type);
	print_ast(node->left, depth + 1, 2);
}

void	print_ast_cmds(t_ast *node)
{
	char	**av;
	int		i;

	i = 0;
	av = node->cmd->argv;
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
	t_redir	**curr;

	printf("REDIRS:\n");
	curr = node->cmd->redirs;
	while (*curr)
	{
		printf("\tTYPE: %d | PATH: %s\n", (*curr)->type, (*curr)->file_path);
		*curr = (*curr)->next;
	}
}

void	print_ast_dfs(t_ast *node)
{
	if (!node)
		return ;
	if (node->cmd)
	{
		print_ast_cmds(node);
		print_ast_redirs(node);
	}
	else
		printf("[NODE %d]\n\n", node->type);
	print_ast_dfs(node->left);
	print_ast_dfs(node->right);
}
