/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:10:58 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 14:17:28 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

bool	is_operator(t_token token);
bool	is_operator(t_token token);
t_token	*find_lowest_prec(t_token *start, t_token *end);
void	*free_mem_arr(char **arr, int index);

t_ast	*create_ast(t_core *core)
{
	t_token	*start;
	t_token	*end;
	t_ast	*ast;

	start = *core->tok_head;
	end = start;
	while (end->next)
		end = end->next;
	ast = parse_tokens(start, end, core);
	return (ast);
}

// Need a function to create a node out of an operator
// and then a function to create a node out of a chain of tokens (commands)
t_ast	*parse_tokens(t_token *start, t_token *end, t_core *core)
{
	t_token	*op;
	t_ast	*new_node;

	op = find_lowest_prec(start, end);
	if (op)
	{
		new_node = create_node(PIPE_NODE, op, op, core);
		new_node->left = parse_tokens(start, op->prev, core);
		new_node->right = parse_tokens(op->next, end, core);
		return (new_node);
	}
	else
	{
		new_node = create_node(CMD_NODE, start, end, core);
		return (new_node);
	}
}

t_ast	*create_node(t_ast_node_type type, t_token *start, t_token *end, t_core *core)
{
	t_ast	*node;

	node = wr_calloc(1, sizeof(t_ast), core);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD_NODE)
	{
		node->cmd = gen_cmd(start, end, core);
    } 
	return (node);
}

t_ast_cmd   *gen_cmd(t_token *start, t_token *end, t_core *core)
{
	t_ast_cmd	*cmd;

	cmd = wr_calloc(1, sizeof(t_ast_cmd), core);
	gen_argv_redir(cmd, start, end, core);
	cmd->cmd_path = get_path(cmd->argv[0], core);
	return (cmd);
}

char	*get_path(char *av_cmd,  t_core *core)
{
	int		i;
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	cmd = ft_split(av_cmd, ' ');
	paths = ft_split(get_env(core, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin2(ft_strjoin(paths[i], "/"), cmd[0], 0);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_tab(cmd);
			ft_free_tab(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_tab(cmd);
	ft_free_tab(paths);
	return (NULL);
}

int		count_words(t_token *start, t_token *end)
{
	int		n;
	t_token	*curr;

	n = 0;
	curr = start;
	while (curr && curr != end)
	{
		if (curr->type == WORD || curr->type == DOLLAR || curr->type == DASH)
			n++;
		curr = curr->next;
	}
	if (curr == end)
		n++;
	return (n);
}

void	gen_argv_redir(t_ast_cmd *cmd, t_token *start, t_token *end, t_core *core)
{
	t_token	*token;
	char	**argv;
	int		n_words;
	int		i;


	token = start;
	n_words = count_words(start, end);
	cmd->argv = wr_calloc(n_tokens + 1, sizeof(char *), core);
	i = 0;
	while (token->next != end)
	{
		if (is_redir_operator(*token))
		{
			if (!is_word(*token->next))
			{
				printf("Syntax error");
				return ;
			}
			else
			{
				add_redir_node(cmd, start, end);
				token = token->next->next;
			}
		}
				
		cmd->argv[i] = ft_substr(token->start, 0, token->length);
		if (!cmd->argv[i])
			return (free_mem_arr(cmd->argv, i));
		i++;
		token = token->next;
	}
	cmd->argv[i] = NULL;
}

void	add_redir_node(t_ast_cmd *cmd, t_token *start, t_token *end)
{
	if (cmd->type == )
}

void	*free_mem_arr(char **arr, int index)
{
	int i;

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

t_token	*find_lowest_prec(t_token *start, t_token *end)
{
	t_token *lowest;
	t_token *token;
	int		prec;
	int		min_prec;

	lowest = NULL;
	min_prec = INT_MAX;
	token = start;
	while (token != end->next)
	{
		if (is_pipe(*token))
		{
			prec = precedence(*token);
			if (prec <= min_prec)
			{
				min_prec = prec;
				lowest = token;
			}
		}
		token = token->next;
	}
	return (lowest);
}

bool	is_pipe(t_token token)
{
	if (token.type == PIPE)
		return (true);
	return (false);
}

bool	is_word(t_token token)
{
	if (token.type == WORD || token.type == DOLLAR || token.type == DASH)
		return (true);
	return (false);
}

bool	is_redir_operator(t_token token)
{
	if (token.type >= REDIR_OUT && token.type <= HERE_DOC)
		return (true);
	return (false);
}

int	precedence(t_token token)
{
	if (token.type == PIPE)
		return (2);
	if (token.type >= REDIR_OUT && token.type <= HERE_DOC)
		return (3);
	else
		return (4);
}

// line: 0 (no line), 1 (right line), 2 (left line)
void	print_ast(t_ast *node, int depth, int line)
{
	int	i;

	if (!node)
		return;

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
	if (node->cmd)
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
	printf("PATH:\n");
	printf("\t%s\n", node->cmd->cmd_path);
	printf("ARGS:\n");
	while (av[i])
	{
		printf("%s,", av[i]);
		i++;
	}
	printf("\n");
}

void	print_ast_dfs(t_ast *node)
{
	if (!node)
		return;

	// Visit node
	if (node->cmd)
	{
		print_ast_cmds(node);
	}
	else
		printf("[NODE %d]\n\n", node->type);

	// Traverse children
	print_ast_dfs(node->left);
	print_ast_dfs(node->right);
}
