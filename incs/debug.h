/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:14 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:14 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# define PRT_VAR (1 << 0)
# define PRT_TOK (1 << 1)
# define PRT_AST (1 << 2)
# define PRT_ALL (PRT_VAR | PRT_TOK | PRT_AST)

// debug.c - Debug functions
void	set_shell_debug(t_shell *shell, char **av);
void	print_env_var(t_variable **vars_ptr);
void	print_tokens(t_shell *shell);
void	print_token_type(t_token *token);

#endif
