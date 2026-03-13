/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:22 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:23 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

// read_line.c - Wrapper for readline
bool	read_line(t_shell *shell);

// heredoc.c - Heredoc functions
void	write_expand(int fd, char *line, t_shell *shell);
void	set_heredoc_delimiter(t_shell *shell, t_token *node);

// get_prompt.c
void	get_prompt(t_shell *shell);

#endif
