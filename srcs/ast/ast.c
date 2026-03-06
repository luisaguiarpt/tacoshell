/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:10:58 by josepedr          #+#    #+#             */
/*   Updated: 2026/02/23 20:23:23 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

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

t_ast	*parse_tokens(t_token *start, t_token *end, t_core *core)
{
	t_token	*op;
	t_ast	*new_node;

	op = find_lowest_prec(start, end);
	if (op)
	{
		new_node = create_ast_node(PIPE_NODE, op, op, core);
		new_node->left = parse_tokens(start, op->prev, core);
		new_node->right = parse_tokens(op->next, end, core);
		return (new_node);
	}
	else
	{
		new_node = create_ast_node(CMD_NODE, start, end, core);
		return (new_node);
	}
}

t_ast	*create_ast_node(t_ast_node_type type,
		t_token *start, t_token *end, t_core *core)
{
	t_ast	*node;

	node = wr_calloc(1, sizeof(t_ast), core);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD_NODE)
		node->cmd = gen_cmd_node(start, end, core);
	return (node);
}

static void	set_syntax_error(t_core *core)
{
	ft_printf_fd(2, "Syntax error.\n");
	core->syntax_error = 2;
	core->exit_status = true;
}

void	gen_argv_redir(t_ast_cmd *cmd,
		t_token *s, t_token *end, t_core *core)
{
	int		n_words;
	int		i;

	n_words = count_cmd_args(s, end);
	if (n_words < 0)
		return (set_syntax_error(core));
	cmd->argv = wr_calloc(n_words + 1, sizeof(char *), core);
	i = 0;
	while (end && s != end->next && s->type != EOF_TOK)
	{
		if (is_redir_operator(*s) && is_word(*s->next))
		{
			add_redir_node(cmd, s, core);
			s = s->next->next;
		}
		else
		{
			cmd->argv[i] = rm_quotes(ft_substr(s->start, 0, s->length), core);
			if (!cmd->argv[i])
				return ((void)free_mem_arr(cmd->argv, i));
			i++;
			s = s->next;
		}
	}
	cmd->argv[i] = NULL;
}
