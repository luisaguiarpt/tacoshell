/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:25 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:26 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// signals.c - Signal setup and handling
void	handle_ctrl_c(t_shell *shell);
void	handle_sigint(int signo);
void	setup_signals(void);
void	disable_parent_signals(void);
void	restore_parent_signals(void);

#endif
