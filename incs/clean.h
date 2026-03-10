/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:10 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:11 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

void	clean(t_shell *shell);
void	exit_clean(t_shell *shell, int exit_code);
void	clean_shell_vars(t_shell *shell);
void	clean_lexer(t_shell *shell);
void	free_tokens(t_token **node_ptr);
void	free_token(t_token *token);
void	clean_redirs(t_redir *redir);
void	clean_ast_cmd(t_ast_cmd *cmd);
void	clean_ast_node(t_ast *node);
void	clean_ast(t_shell *shell);
void	free_array(char **array);


#endif
