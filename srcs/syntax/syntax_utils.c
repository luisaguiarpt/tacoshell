/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:56:08 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/15 14:56:10 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	set_syntax_err_tok(t_shell *shell, t_token *token, int exit_status)
{
	if (token->type == TK_EOF)
		ft_printf_fd(2, ERRMSG_TOK, "newline");
	else
		ft_printf_fd(2, ERRMSG_TOK, token->word);
	shell->syntax_error = true;
	shell->exit_status = exit_status;
}

void	set_syntax_err_str(t_shell *shell, char *str, int exit_status)
{
	ft_printf_fd(2, ERRMSG_TOK, str);
	shell->syntax_error = true;
	shell->exit_status = exit_status;
}

void	set_syntax_err_quotes(t_shell *shell, char *str, int exit_status)
{
	ft_printf_fd(2, ERRMSG_QUOTES, str);
	shell->syntax_error = true;
	shell->exit_status = exit_status;
}
