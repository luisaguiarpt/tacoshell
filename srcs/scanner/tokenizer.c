/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:16:29 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:16:30 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tacoshell.h"

t_token	create_token(t_token_type type, t_scanner *scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.length = (int)(scanner->current - scanner->start);
	if (type == STRING_DQ || type == STRING_SQ)
	{
		token.start++;
		token.length -= 2;
	}
	token.prev = NULL;
	token.next = NULL;
	return (token);
}

t_token	error_token(t_token_type type, t_scanner *scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.length = (int)(scanner->current - scanner->start);
	token.prev = NULL;
	token.next = NULL;
	return (token);
}

void	append_token(t_token **head, t_token *new)
{
	t_token *tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	handle_error_tok(t_token *token, t_scanner *scanner)
{
	if (token->type == ERROR_TOK_SQ)
	{
		scanner->core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, "error: Unterminated string: ");
		ft_printf_fd(STDERR_FILENO, "missing matching `\'\'.\n");
		return ;
	}
	else if (token->type == ERROR_TOK_DQ)
	{
		scanner->core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, "error: Unterminated string: ");
		ft_printf_fd(STDERR_FILENO, "missing matching `\"\'.\n");
		return ;
	}
	else if (token->type == ERROR_TOK_BR)
	{
		scanner->core->syntax_error = true;
		ft_printf_fd(STDERR_FILENO, "error: Unimplemented operator.\n");
		return ;
	}
}

void	link_tok(t_scanner *scanner, char *flag)
{
	t_token	*token;

	while (1)
	{
		token = wr_calloc(1, sizeof(t_token), scanner->core);
		*token = scan_token(scanner);
		append_token(scanner->core->tok_head, token);
		if (token->type == ERROR_TOK_SQ || token->type == ERROR_TOK_DQ)
			return (handle_error_tok(token, scanner));
		if (token->type == EOF_TOK)
			break ;
	}
	if (!flag)
		return ;
	print_tok(*scanner->core->tok_head);
}
