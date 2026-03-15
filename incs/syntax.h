/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:19 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:20 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# define ERRMSG_PIPE "syntax error near unexpected token `|'\n"
# define ERRMSG_TOK "syntax error near unexpected token `%s'\n"
# define ERRMSG_QUOTES "syntax error: missing matching `%s'\n"

// syntax.c
void		check_syntax(t_shell *shell);
void		syntax_pipe_start(t_shell *shell);
void		syntax_pipe_end(t_shell *shell);
void		syntax_redirs(t_shell *shell);
void		syntax_quotes(t_shell *shell, t_token *token);
void		syntax_operators_start(t_shell *shell);
void		syntax_operators_end(t_shell *shell);

// syntax_utils.c
void		set_syntax_error_tok(t_shell *shell, t_token *token, int exit_status);
void		set_syntax_error_str(t_shell *shell, char *str, int exit_status);
void		set_syntax_error_quotes(t_shell *shell, char *str, int exit_status);

// syntax_misc.c
bool		is_token_operator(t_token *token);

#endif
