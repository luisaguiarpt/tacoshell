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

# define ERR_MSG_PIPE "syntax error near unexpected token `|'\n"

void	check_syntax(t_shell *shell);
void	syntax_pipe_start(t_shell *shell);

#endif
