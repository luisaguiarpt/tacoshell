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

# define ERRMSG_HD_EOF \
	"warning: here-document at line %d delimited by end-of-file (wanted `%s')\n"

// read_line.c - Wrapper for readline
bool	read_line(t_shell *shell);
int		count_heredocs(t_redir *head);

// heredoc.c - Heredoc functions
int		heredoc_read(t_redir *curr, int heredoc_curr, t_shell *shell);
void	heredoc_read_loop(t_shell *shell, int fd, char *delimiter);
void	set_heredoc_delimiter(t_shell *shell, t_token *node);
bool	check_delimiter(char *line, char *delimiter);
void	write_expand(int fd, char *line, t_shell *shell);

// get_prompt.c
void	get_prompt(t_shell *shell);

#endif
