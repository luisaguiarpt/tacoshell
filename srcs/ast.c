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

t_ast	create_ast(t_core *core)
{
	t_token	*start;
	t_token	*end;
	t_ast	ast;

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
	t_ast	node;

	op = find_lowest_prec(start, end);
	if (!op)
		return (create_node(CMD, start, end, core));
	else
		return (create_node(PIPE, start, end, core));
	node = create_node(op);
}

t_ast	*create_node(t_token_type type, t_token *start, t_token *end, t_core *core)
{
	t_ast	*node;

	node = wr_calloc(1, sizeof(t_ast), core);
	node->type = type;
	if (type == CMD)
	{
		node->cmd = gen_cmd(start, end, core);
    } 
	return (node);
}

t_ast_cmd   gen_cmd(t_token *start, t_token *end, t_core *core)
{
	t_ast_cmd	cmd;

	cmd = wr_calloc(1, sizeof(t_ast_cmd), core);
	cmd.argv = gen_argv(start, end, core);
	cmd.cmd_path = get_path(argv[0], core.env);
}

char	*get_path(char *av_cmd, char **ep)
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

int		count_tokens(t_token *start, t_token *end)
{
	int		n;
	t_token	*curr;

	n = 0;
	curr = start;
	while (curr && curr != end)
	{
		n++;
		curr = curr->next;
	}
	if (curr == end)
		n++;
	return (n);
}

char	**gen_argv(t_token *start, t_token *end, t_core *core)
{
	t_token	*token;
	char	**argv;
	int		n_tokens;
	int		i;


	token = start;
	n_tokens = count_tokens(start, end);
	argv = wr_calloc(n_tokens + 1, sizeof(char *), core);
	i = 0;
	while (i < n_tokens)
	{
		argv[i] = ft_substr(core.line, token->start, token->length);
		if (!argv[i])
			return (free_mem_arr(argv, i));
		i++;
	}
	argv[i] = NULL;
	return (argv);
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
		if (is_operator(&token))
		{
			prec = precedence(&token);
			if (prec <= min_prec)
			{
				min_prec = prec;
				lowest = t;
			}
		}
	}
	return (lowest);
}

bool	is_operator(t_token token)
{
	if (token.type == REDIR_OUT || token.type == REDIR_IN || token.type == PIPE)
		return (true);
	if (token.type == APPEND || token.type == HERE_DOC)
		return (true);
	return (false);
}

bool	precedence(t_token token)
{
	if (token.type == PIPE)
		return (PREC_1);
	if (token.type == REDIR_IN || token.type == REDIR_OUT)
		return (PREC_2);
	if (token.type == APPEND || token.type == HERE_DOC)
		return (PREC_2);
	else
		return (4);
}
