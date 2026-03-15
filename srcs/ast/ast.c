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

#include "../incs/minishell.h"

t_ast	*create_ast(t_shell *shell)
{
	t_token	*start;
	t_token	*end;
	t_ast	*ast;

	start = *shell->tokens;
	end = last_token(shell);
	ast = parse_tokens(start, end, shell);
	return (ast);
}

t_ast	*parse_tokens(t_token *start, t_token *end, t_shell *shell)
{
	t_token	*op;
	t_ast	*new_node;

	op = find_lowest_prec(start, end);
	if (op)
	{
		new_node = create_ast_node(PIPE_NODE, op, op, shell);
		new_node->left = parse_tokens(start, op->prev, shell);
		new_node->right = parse_tokens(op->next, end, shell);
		return (new_node);
	}
	else
	{
		new_node = create_ast_node(CMD_NODE, start, end, shell);
		return (new_node);
	}
}

t_ast	*create_ast_node(t_ast_node_type type,
		t_token *start, t_token *end, t_shell *shell)
{
	t_ast	*node;

	node = wr_calloc(1, sizeof(t_ast), shell);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == CMD_NODE)
		node->cmd = gen_cmd_node(start, end, shell);
	return (node);
}

void	gen_argv_redir(t_ast_cmd *cmd,
		t_token *s, t_token *end, t_shell *shell)
{
	int		n_words;
	int		i;

	n_words = count_cmd_args(s, end);
	if (n_words < 0)
		return (set_syntax_error_tok(shell, s->next, 2));
	cmd->argv = wr_calloc(n_words + 1, sizeof(char *), shell);
	i = 0;
	while (end && s != end->next && s->type != TK_EOF)
	{
		if (is_redir_operator(*s) && is_word(*s->next))
		{
			add_redir_node(cmd, s, shell);
			s = s->next->next;
		}
		else
		{
			cmd->argv[i] = ft_strdup(s->word);
			if (!cmd->argv[i])
				return ((void)free_mem_arr(cmd->argv, i));
			i++;
			s = s->next;
		}
	}
	cmd->argv[i] = NULL;
}
