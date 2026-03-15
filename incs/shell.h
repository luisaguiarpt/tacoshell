/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:28 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:29 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

// shell_init.c - shell struct initialization
t_shell	init_shell(char **av, char **ep);
void	set_shell_null(t_shell *shell);
void	init_tokens_ptr(t_shell *shell);
void	init_shell_vars_ptr(t_shell *shell);
void	setup_signals(void);

#endif
